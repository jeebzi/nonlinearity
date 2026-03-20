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
