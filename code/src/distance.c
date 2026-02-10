#include "distance.h"

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
			printf("%lu + %lu\n", mot[j],base[i*int_par_ligne + j]); 
			mot[j] ^= base[i*int_par_ligne + j];
			wt += __builtin_popcountl(mot[i]);
			j += 1;
		}
		printf("wt %d\n", wt);
		if (wt < score) score = wt;
		cpt += 1;
	}
	return score;
}


