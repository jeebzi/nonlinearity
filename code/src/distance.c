#include "distance.h"
#include "util.h"
#include "boole.h"

int distance_mot_code_zip(uint64_t *mot, uint64_t *base, int ffsize, int nb_ligne) {
	/*
	 * calcule la distance d'un mot à un code (base) de manière plus efficace avec la représentation par entier
	 * je pense que le mot est modifié par cette fonction
	 */
	int int_par_ligne = (ffsize+63) / 64;
	int score = ffsize;
	uint64_t limite = (uint64_t)1 << nb_ligne;
	uint64_t cpt = 1;
	int i; // indice bit qui change
	int j, wt;
	while (cpt < limite) {
		i = __builtin_ctzl(cpt);
		//addition entre mot dans F2
		j = 0;
		wt = 0;
		while (j < int_par_ligne) {
			mot[j] ^= base[i*int_par_ligne + j];
			wt += __builtin_popcountl(mot[j]);
			j += 1;
		}
		if (wt < score) score = wt;
		cpt += 1;
	}
	return score;
}

int distance_mot_code_min(uint64_t *mot, uint64_t *base, uint64_t ffsize, int nb_ligne, int target) {
	/*
	 * calcule la distance entre un mot et un code, renvoie la valeur de la distance si elle et supérieure ou égale
	 * à la target -1 sinon
	 */
	int int_par_ligne = (ffsize+63) / 64;
	int score = weight_64(mot, int_par_ligne);
	uint64_t limite = (uint64_t)1 << nb_ligne;
	uint64_t cpt = 1;
	int i; // indice bit qui change
	int j, wt;
	while (cpt < limite) {
		i = __builtin_ctzl(cpt);
		//addition entre mot dans F2
		j = 0;
		wt = 0;
		while (j < int_par_ligne) {
			mot[j] ^= base[i*int_par_ligne + j];
			wt += __builtin_popcountl(mot[j]);
			j += 1;
		}
		if (wt < target || (ffsize - wt) < target) return -1;
		if (wt < score) score = wt;
		cpt += 1;
	}
	return score;
}


int *distribution_distance(uint64_t *mot, uint64_t *base, int ffsize, int nb_ligne) {
	/*
	 * calcule la distance entre unt mot et tous les mots du code généré par la base et renvoi la distribution
	 * dans un tableau d'entier
	 */
	int *res, int_par_ligne = (ffsize+63)/64, i, j, wt;
	uint64_t cpt = 1, limite = (uint64_t)1 << nb_ligne;
	res = (int*) calloc(ffsize, sizeof(int));
	
	wt = weight_64(mot, int_par_ligne);
	res[wt] += 1;

	//calcule des poids des mots du coset comme dans la fonction du haut
	while (cpt < limite) {
		i = __builtin_ctzl(cpt);
		//addition entre mot dans F2
		j = 0;
		wt = 0;
		while (j < int_par_ligne) {
			mot[j] ^= base[i*int_par_ligne + j];
			wt += __builtin_popcountl(mot[j]);
			j += 1;
		}
		res[wt] += 1;
		cpt += 1;
	}
	return res;
}

int distance_probabiliste(code c, uchar *boole, int ffsize, int nb_tour, int target) {
	/*
	 * estime de manière probabiliste en utilisant la technique du pivot de Gauss la distance entre une
	 * fonction et un code, renvoie une distance min au code possible si elle est supérieur ou égale à
	 * la target -1 sinon
	 */
	uint64_t *mot, *words, *mot_cpy, *words_cpy;
	int int_par_ligne = (c.longueur+63)/64, nb_int_mat = c.dim*int_par_ligne, j;
	mot = boole_to_int(boole, ffsize);
	words = code_to_int(c);

	int cpt = 0, score = ffsize, wt;
	while (cpt < nb_tour) {
		mot_cpy = copy_uint64(mot, int_par_ligne);
		words_cpy = copy_uint64(words, nb_int_mat);

		pivotage(words_cpy, mot_cpy, ffsize, c.dim, int_par_ligne);
		//calcul poid du mot obtenu
		j = 0;
		wt = 0;
		while (j < int_par_ligne) {
			wt += __builtin_popcountl(mot_cpy[j]);
			j += 1;
		}
		if (wt < target) {
			free(mot_cpy);
			free(words_cpy);
			free(mot);
			free(words);
		       	return -1;
		}
		if (wt < score) score = wt;
		cpt += 1;
		free(mot_cpy);
		free(words_cpy);
	}
	free(mot);
	free(words);
	return score;
}

int distance_decode(uint64_t *mot, code64 c, code64 c2, int target, int ffdimen, int degree) {
	/*
	 * calcule la distance entre un mot et un code avec la méthode de fourquet dumer tavernier
	 */
	assert((1 << ffdimen) == c.longueur);
	assert(c.longueur == (c2.longueur << 1));
	int best, int_par_ligne = (c.longueur+63) / 64, dist;
	best = weight_64(mot, int_par_ligne);

	// pour chaque u dans RM(k - 1, ffdimen - 1)
	uint64_t limite = (uint64_t)1 << rmdimen(degree - 1, ffdimen - 1);
	uint64_t cpt = 1;
	uint64_t *L, *R, *W, *u; // partie gauche et droit du mot avec W le résultat de (L+R+u)
	uint64_t **zip, **cpy_zip; // le pointeur que contient la partie gauche et droite du mot
	zip = split(mot, c.longueur, int_par_ligne);
	cpy_zip = split(mot, c.longueur, int_par_ligne);

	// déclaration code linéaire
	code code_lineaire = RM(degree - 1, ffdimen - 1);
	uint64_t *code_lin = code_to_int(code_lineaire);

	L = zip[0];
	R = zip[1];
	int i, j, nb_int, wt;
	// nombre d'entier pour représenter un mot dans RM(k - 1, ffdimen - 1)
	nb_int = ((1 << (ffdimen - 1)) + 63) / 64;

	u = (uint64_t*) calloc(nb_int, sizeof(uint64_t));
	W = (uint64_t*) calloc(nb_int, sizeof(uint64_t));
	int over = 0;
	while (cpt < limite && over == 0) {
		i = __builtin_ctzl(cpt);
		wt = 0;
		j = 0;
		while (j < nb_int) {
			u[j] ^= code_lin[i*nb_int + j];
			// on doit aussi additioner la partie gauche et droite du mot avec u
			W[j] = u[j] ^ L[j] ^ R[j];
			wt += __builtin_popcountl(W[j]);
			j += 1;
		}
		if (wt < best) {
			// préparer copy zip
			 j = 0;
			 while (j < nb_int) {
				 cpy_zip[1][j] = zip[1][j] ^ u[j];
				 j += 1;
			 }
			// a faire bdistance
			dist = bdistance(cpy_zip, c2, target, nb_int);
			if (dist < target) { best = -1; over = 1; }
			if (dist < best) best = dist;
		}
		cpt += 1;
	}
	
	//free
	free_code(code_lineaire);
	free(code_lin);
	free(W);
	free(u);
	free(L);
	free(R);
	free(zip);
	free(cpy_zip[0]);
	free(cpy_zip[1]);
	free(cpy_zip);

	return best;
}

int bdistance(uint64_t **zip, code64 c, int target, int int_par_ligne) {
	/*
	 * prend un mot f représenté de cette forme [L | R] avec zip[0] = L et zip[1] = R
	 * et renvoie la distance au code à une variable de plus par rapport au code c
	 */
	int best = c.longueur << 1;
	uint64_t *v, v1, v2; // v énumère tous les mot de c
	v = (uint64_t*) calloc(int_par_ligne, sizeof(uint64_t));
	int wt=0, i, j;
	uint64_t limite = (uint64_t)1 << c.dim, cpt = 1;
	while (cpt < limite) {
		i = __builtin_ctzl(cpt);
		j = 0;
		wt = 0;
		while (j < int_par_ligne) {
			v[j] ^= c.G[i * int_par_ligne + j];
			// copy de v[j] qui vont être additionner avec L et R
			v1 = v[j] ^ zip[0][j];
			v2 = v[j] ^ zip[1][j];

			wt += __builtin_popcountl(v1) + __builtin_popcountl(v2);
			j += 1;
		}
		if (wt < target) { free(v); return -1; }
		if (wt < best) best = wt;
		cpt += 1;
	}
	free(v);
	return best;
}

int ftl(uint64_t *f, int ffdimen, int ffsize, int target) {
	/*
	 * calcule la non linéarité d'une fonction booléenne grâce au décodeage de liste de Fourquet Tavernier
	 * fonction uniquement pour RM(2, 8) pour l'instant
	 */
	assert(ffdimen >= 7);
	assert(ffsize == (1 << ffdimen));
	int int_par_ligne = (ffsize+63)/64;
	int int_par_ligne2 = ((ffsize >> 1) + 63) / 64;
	int j, i, k, over = 0, wt=-1;
	unsigned int score = 0;
	code tmp;
	tmp = RMH(2, ffdimen - 1);
	code64 base_quad = code_to_code64(tmp);
	free_code(tmp);
	tmp = RMH(1, ffdimen - 1);
	code64 base_lin = code_to_code64(tmp);
	free_code(tmp);

	uint64_t *p; /* prefix de q dans rm(2,8) */
	uint64_t *l, *y, *fpp;
	p = calloc(int_par_ligne2, sizeof(uint64_t));
	l = calloc(int_par_ligne, sizeof(uint64_t));
	y = calloc(int_par_ligne, sizeof(uint64_t));
	fpp = calloc(int_par_ligne, sizeof(uint64_t));

	uint64_t lim_quad, cpt_quad, lim_lin, cpt_lin;
	lim_quad = (uint64_t) 1 << base_quad.dim;
	lim_lin = (uint64_t) 1 << base_lin.dim;
	cpt_quad = 0;

	/*restriction f0 f1 */
	uint64_t *f0, *f1, **zip;
	zip = split(f, ffsize, int_par_ligne);
	f0 = zip[0];
	f1 = zip[1];
	free(zip);
	/* variable pour stocker f0 + P et f1 + P */
	uint64_t *f0p, *f1p;
	f0p = calloc(int_par_ligne2, sizeof(uint64_t));
	f1p = calloc(int_par_ligne2, sizeof(uint64_t));
	unsigned int gamma0, gamma1, gamma;
	while (over == 0 && cpt_quad < lim_quad) {
		if (cpt_quad == 0) {
			gamma0 = sup_walsh(f0, ffdimen - 1, ffsize >> 1);
			gamma1 = sup_walsh(f1, ffdimen - 1, ffsize >> 1);
		}
		else {
			i = __builtin_ctzl(cpt_quad);
			j = 0;
			while (j < int_par_ligne2) {
				p[j] ^= base_quad.G[i*int_par_ligne2 + j];
				f0p[j] = p[j] ^ f0[j];
				f1p[j] = p[j] ^ f1[j];
				j += 1;
			}
			gamma0 = sup_walsh(f0p, ffdimen - 1, ffsize >> 1);
			gamma1 = sup_walsh(f1p, ffdimen - 1, ffsize >> 1);
		}
		 printf("gamma0 %d + gamma 1 %d = %d\n",gamma0, gamma1, gamma0 + gamma1);
		if ((gamma0 + gamma1) >= score) {
			memset(l, 0, int_par_ligne*sizeof(uint64_t));
			cpt_lin = 0;
			while (over == 0 && cpt_lin < lim_lin) {
				if (cpt_lin == 0) {
					/* création de f + p  avec p sur m + 1 variable [p|p]*/
					j = 0;
					while (j < int_par_ligne) {
						fpp[j] = f[j] ^ p[j%int_par_ligne2];
						y[j] = fpp[j];
						j += 1;
					}
				}
				/* on regarde y = f + p + x_8l */
				else {
					i = __builtin_ctzl(cpt_lin);
					j = 0;
					k = int_par_ligne2;
					/* l = [0|l] */
					while (j < int_par_ligne2) {
						l[k] ^= base_lin.G[i*int_par_ligne2 + j];
						y[k] = fpp[k] ^ l[k];
						k += 1;
						j += 1;
					}
				}
				gamma = sup_walsh(y, ffdimen, ffsize);
				if (gamma > score) {
					score = gamma;
					wt = (ffsize >> 1) - (score >> 1);
					if (wt < target) over = 1;
				}
				cpt_lin += 1;
			}
		}
		cpt_quad += 1;
		// printf("cpt_quad %lu lim %lu\n", cpt_quad, lim_quad);
	}


	free(l);
	free(p);
	free(base_quad.G);
	free(base_lin.G);
	free(f0p);
	free(f1p);
	free(f0);
	free(f1);
	free(fpp);
	free(y);
	if (over == 1) return -1;
	return wt;
}

int non_linearite_walsh(int *signe, int ffsize) {
	/*
	 * prend une fonction booléenne en représentation signe et renvoie ça non linéarité
	 * d'ordre 1 en calculant son rayon spectral
	 */
	fourier_transform(signe, ffsize);
	// parcourir le tableau signe qui est mainenant les coef de walsh pour trouver le max
	int spec= abs(signe[0]);
	int i = 1;
	while (i < ffsize) {
		if (abs(signe[i] > spec))
			spec = abs(signe[i]);
		i += 1;
	}
	/* valeur non linéarité d'ordre 1
	 * NL(f) = 2^(m-1) - 1/2 * R(f)
	 */
	return (ffsize >> 1) - (spec >> 1);
}

