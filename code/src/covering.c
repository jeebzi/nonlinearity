#include "covering.h"

uint64_t *get_covering(uint64_t *mot, code64 c, int poid_min) {
	/*
	 * renvoie le covering du coset générer par mot si la distance entre le mot et le code est
	 * connu le spécifié dans poind_min sinon le mettre à -1 et cela devra être calculé
	 */
	uint64_t *res;
	//on doit énumérer le coset et pour tous ces éléments si leur poid et égale au poid min
	// on l'additionne au résultat qui représente en binaire le covering de mot
	int int_par_ligne = (c.longueur+63)/64;
	res = (uint64_t*) calloc(int_par_ligne, sizeof(uint64_t));
	uint64_t limite = ((uint64_t)1 << c.dim), cpt = 1;
	int i, j, wt;
	while (cpt < limite) {
		i = __builtin_ctzl(cpt);
		wt = 0;
		j = 0;
		while (j < int_par_ligne) {
			mot[j] ^= c.G[i*int_par_ligne + j];
			wt += __builtin_popcountl(mot[j]);
			j += 1;
		}
		j = 0;
		if (wt < poid_min ||poid_min == -1) { // si on trouve un nouveau poid minimal du coset on doit remettre le résultat à 0 et additionner le nouveau leader qui sera fait au prochain if
			res = (uint64_t*) memset((void*) res, 0, int_par_ligne*sizeof(uint64_t));
			poid_min = wt;
		}
		if (wt == poid_min) { // si on trouve un leader on l'additionne au résultat
			while (j < int_par_ligne) {
				res[j] |= mot[j];
				j += 1;
			}
		}
		cpt += 1;
	}
	return res;
}

int is_orphan(uint64_t *mot, code64 c, int poid_min) {
	/*
	 * renvoi 1 si le mote est un orphan/arcoset 0 sinon
	 */
	uint64_t *res = get_covering(mot, c, poid_min);
	// on regarde si res à des 1 partout
	int j = 0;
	int int_par_ligne = (c.longueur+63) / 64;
	int wt = 0;
	while (j < int_par_ligne) {
		 wt += __builtin_popcountl(res[j]);
		 j += 1;
	}
	free(res);
	if (wt == c.longueur) return 1;
	return 0;
}
