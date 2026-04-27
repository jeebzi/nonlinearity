#include "weight.h"

int weight_64(uint64_t *p, int n) {
	/*
	 * renvoi le poid binaire de tous les uint64 du tableau de taille n
	 */
	int wt = 0;
	int i = 0;
	while (i < n) {
		wt += __builtin_popcountl(p[i]);
		i += 1;
	}
	return wt;
}

int* tableau_poid(uint64_t *h, code64 c) {
	/*
	 * renvoie le tableau W tel que W[q] = wt(h+q) pour chaque q dans le code
	 */
	int ffsize = c.longueur;
	int *res, int_par_ligne = (63+ffsize)/64;
	/* calcule de la taille du tableau */
	uint64_t taille_tab = (uint64_t) 1 << c.dim;
	res = calloc(taille_tab, sizeof(int));

	/*on parcour tousles q et on calcule le poid*/
	uint64_t *q;
	q = calloc(int_par_ligne, sizeof(uint64_t));
	int i, j, wt;
	uint64_t cpt = 0, indice = 0;
	while (cpt < taille_tab) {
		if (cpt == 0) {
			res[0] = weight_64(h, int_par_ligne);
			cpt += 1;
		}
		i = __builtin_ctzl(cpt);
		indice ^= (1 << i);
		wt = 0;
		j = 0;
		while (j < int_par_ligne) {
			q[j] ^= c.G[i*int_par_ligne + j];
			wt += __builtin_popcountl(q[j] ^ h[j]);
			j += 1;
		}
		res[indice] = wt;
		cpt += 1;
	}
	return res;
}

