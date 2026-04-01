#include "util.h"

uint64_t* copy_uint64(uint64_t *src, int n) {
	/*
	 * copy n élément d'un tableau de uint64
	 */
	uint64_t *dst;
	dst = (uint64_t*) malloc(n*sizeof(uint64_t));

	int i = 0;
	while (i < n) {
		dst[i] = src[i];
		i += 1;
	}
	return dst;
}

int max_tab_int(int *tab, int n) {
	/*
	 * renvoie la valeur max d'un tableau d'entier non trié
	 */
	int maxi;
	int i = 1;
	maxi = tab[0];
	while (i < n) {
		if (tab[i] > maxi) maxi = tab[i];
		i += 1;
	}
	return maxi;
}
