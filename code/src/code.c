#include "code.h"

code init_code(int dim, int longueur) {
	/*
	 * initialise un code.
	 * int longeur: nombre col
	 * int dim: nombre de ligne
	 * uchar *G: matrice génératrice rerpésenté en une dimension
	 * int *pivot: tableau des pivot utilisé
	 */
	code res;
	
	res.dim = dim;
	res.longueur = longueur;
	res.G = (uchar*) calloc(dim * longueur, sizeof(uchar));
	res.pivot = (int*) calloc(dim, sizeof(int));
	return res;
}

void free_code(code c) {
	free(c.G);
	free(c.pivot);
	c.G = NULL;
	c.pivot = NULL;
}

code RMH(int k, int m) {
	/*
	 * initialse un code de Reed-Muller homogène de degrée k et à m variable
	 */
	code res;
	int nb_col = 1 << m;
	res = init_code(  binomial(k, m), nb_col );
	int u = 0, x;
	int num_ligne = 0;
	while (u < nb_col) {
		if (__builtin_popcount(u) == k ) {
			x = 0;
			while (x < nb_col) {
				res.G[num_ligne*nb_col + x] = (u&x) == u;
				x += 1;
			}
			num_ligne += 1;
		}
		u += 1;
	}
	assert(num_ligne == res.dim);
	return res;
}
code RM(int k, int m) {
	/*
	 * initialse un code de Reed-Muller de degrée k et à m variable
	 */
	code res;
	int nb_col = 1 << m;
	res = init_code(rmdimen(k, m), nb_col);
	int u = 0, x;
	int num_ligne = 0;
	while (u < nb_col) {
		if (__builtin_popcount(u) <= k) {
			x = 0;
			while (x < nb_col) {
				res.G[num_ligne*nb_col + x] = (u&x) == u;
				x += 1;
			}
			num_ligne += 1;
		}
		u += 1;
	}
	assert(num_ligne == res.dim);
	return res;
}


int binomial(int k, int m){
	/*
	 * renvoie k parmi m
	 */
	if (k==0){
		return 1;
	}

	int step1 = m - k + 1;
	int step0;
	for(int i = 1 ; i < k; i++){
		step0 = step1;
		step1 = step0 * (m-k+1+i)/(i+1);
	}
	return step1;
}

int rmdimen(int k, int m){
	/*
	 * revoie la dimension du code de Reed-Muller de degrée k à m variable
	 */
	int somme = 0;
	for(int i = 0 ; i <= k ; i++ ){
		somme = somme + binomial(i,m);
	}
	return somme;
}

unsigned char* extraire_ligne(code c, int num_ligne) {
	/*
	 * renvoie une ligne de la matrice génératrice du code
	 */
	unsigned char *res;
	res = (unsigned char*) calloc(c.longueur, sizeof(unsigned char));
	int i = 0;
	while (i < c.longueur) {
		res[i] = c.G[num_ligne*c.longueur + i];
		i += 1;
	}
	return res;
}

int calcule_distance_mot_code(code c, unsigned char *boole, int ffsize) {
	/*
	 * calcule la distance d'une fonctin booléenne à un code
	 * change ce qu'il y a dans boole !
	 */
	int dist = ffsize;
	int b, w;
	uint64_t limite, cpt = 1;
	limite = ((uint64_t) 1) << (c.dim);
	unsigned char *ligne;

	while (cpt < limite) {
		b = __builtin_ctzl(cpt);
		ligne = extraire_ligne(c, b);
		add_boole(boole, ligne, ffsize);
		free(ligne);
		w = weight_boole(boole, ffsize);

		if (w < dist) dist = w;
		cpt += 1;
	}
	return dist;
}

uint64_t* code_to_int(code c) {
	/*
	 * prend un code et renvoie ça matrice génératrice représenté par un tableau de uint64
	 */
	uint64_t *res;
	int int_par_ligne = (c.longueur+63) / 64;
	int i = 0, k = 0, j;
	res = (uint64_t*) calloc(c.dim*int_par_ligne, sizeof(uint64_t*));
	while (i < c.dim) {
		j = 0;
		while (j < c.longueur) {
			if (c.G[k] == 1)
				res[i*int_par_ligne + (j/64)] |= (uint64_t)1 << (j%64);
			k += 1;
			j += 1;
		}
		i += 1;
	}
	return res;
}

void pivotage(uint64_t *words, uint64_t *mot, int ffsize, int nb_ligne, int int_par_ligne) {
	/*
	 * effectue le pivot de gauss en mettant des 0 et en bas en choisissant le pivot de façon aléatoire
	 * renvoie le tableau des indices de pivot utilisé
	 */
	int pivot;
	int i, j, k, add_mot=0;
	for (i = 0; i < nb_ligne; i++) {
		do {
			pivot = rand() % ffsize;
		}
		while (((words[i*int_par_ligne + (pivot/64)] >> (pivot%64)) & 1) != 1);

		// savoir si on fait l'addition entre la ligne pivot et le mot
		if (((mot[pivot/64] >> pivot%64) & 1) == 1) add_mot = 1;

		for (j = 0; j < nb_ligne; j++) {
			if (((words[j*int_par_ligne + (pivot/64)] >> (pivot%64)) & 1) == 1 && j != i) {
				// ajoute les lignes
				k = 0;
				// si on doit additionner le mot on le fait pendant la boucle d'addition de ligne
				if (add_mot == 1) {
					while (k < int_par_ligne) {
						words[j*int_par_ligne + k] ^= words[i*int_par_ligne + k];
						mot[k] ^= words[i*int_par_ligne + k];
						k += 1;
					}
					add_mot = 0;
				}
				// sinon on ajoute juste deux lignes entre elles
				else {
					while (k < int_par_ligne) {
						words[j*int_par_ligne + k] ^= words[i*int_par_ligne + k];
						k += 1;
					}
				}
			}
		}
		// si on doit additioner le mot mais que aucune ligne ne ne l'a été on fait l'addition maintenant
		if (add_mot == 1) {
			while (k < int_par_ligne) {
				mot[k] ^= words[i*int_par_ligne + k];
				k += 1;
			}
			add_mot = 0;
		}
	}
}

