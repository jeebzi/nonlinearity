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
	 * calcule la distance entre un mot et un code, renvoie la valeur de la distance si elle st supérieure ou égale
	 * à la target -1 sinon
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
		if (wt < target) return -1;
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

int distance_decode(uint64_t *mot, uint64_t *base, int target, int ffdimen, int ffsize, int degree) {
	/*
	 * calcule la distance entre un mot et un code avec la méthode de fourquet dumer tavernier
	 */
	int best = ffsize, int_par_ligne = (ffsize+63) / 64, dist;

	// pour chaque u dans RM(1, ffdimen - 1)
	uint64_t limite = (uint64_t)1 << rmdimen(1, ffdimen - 1);
	uint64_t cpt = 1;
	uint64_t *L, *R, *W, *u; // partie gauche et droit du mot avec W le résultat de (L+R+u)
	uint64_t **zip; // le pointeur que contient la partie gauche et droite du mot
	zip = split(mot, ffsize, int_par_ligne);

	// déclaration code linéaire
	code code_lineaire = RM(1, ffdimen);
	uint64_t *code_lin = code_to_int(code_lineaire);

	L = zip[0];
	R = zip[1];
	int i, j, nb_int, wt;
	// nombre d'entier pour représenter un mot dans RM(1, ffdimen - 1)
	nb_int = ((1 << (ffdimen - 1)) + 63) / 64;

	u = (uint64_t*) calloc(nb_int, sizeof(uint64_t));
	while (cpt < limite) {
		i = __builtin_ctzl(cpt);
		wt = 0;
		j = 0;
		while (j < nb_int) {
			u[j] ^= code_lin[i*nb_int + j];
			// on doit aussi additioner la partie gauche et droite du mot avec u
			W[j] ^= u[j] ^ L[j] ^ R[j];
			wt += __builtin_popcountl(W[j]);
			j += 1;
		}
		if (wt < best) {
			// a faire bdistance
			dist = bdistance(zip, degree, ffdimen);
			if (dist < target) return - 1;
			if (dist < best) best = dist;
		}
		cpt += 1;
	}
	
	//free
	free(code_lin);
	free(W);
	free(u);
	free(L);
	free(R);
	free(zip);

	return best;
}
