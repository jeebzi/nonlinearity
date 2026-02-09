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
