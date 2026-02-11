#include "affichage.h"

void print_tab_uint64(uint64_t *tab, int n) {
	int i = 0;
	while (i < n) {
		printf("%lu ", tab[i]);
		i += 1;
	}
	printf("\n");
}

void print_tab_int(int *tab, int n) {
	int i = 0;
	while (i < n) {
		printf("%d ", tab[i]);
		i += 1;
	}
	printf("\n");
}

void print_distribution(int *distribution, int n) {
	/*
	 * affiche la distribution des distances
	 */
	int i = 0, nb;
	while (i < n) {
		nb = distribution[i];
		if (nb != 0) printf("%d:%d ", i, nb);
		i += 1;
	}
	printf("\n");
}
