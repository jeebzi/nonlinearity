#include <all.h>
#include "../include/include.h"

/* le but de ce programme est de construire le tableau L tel que L[q] = max wt(h+q+l) avec h nos
 * fonctions HNL pour RM(2,7) q les quadratique homogènes et l les fonctions affines
 */

int *tableau_poid_max(uint64_t *h, int ffdimen, int ffsize) {
	int int_par_ligne = (ffsize+63)/64;
	int *tab; /* tableau des poid */
	int id_tab = 0;
	int max = 0;

	code base_tmp = RMH(2, ffdimen);
	code64 base_quad = code_to_code64(base_tmp);
	free_code(base_tmp);
	unsigned int longueur_tab = 1 << base_quad.dim;
	tab = (int*) calloc(longueur_tab, sizeof(int));
	base_tmp = RM(1, ffdimen);
	code64 base_affine = code_to_code64(base_tmp);
	free_code(base_tmp);
	unsigned int limite = 1 << base_affine.dim;

	uint64_t *q, *l;
	q = (uint64_t*) calloc(int_par_ligne, sizeof(uint64_t));
	l = (uint64_t*) calloc(int_par_ligne, sizeof(uint64_t));
	unsigned int cpt = 1, cpt2;
	int j, wt, i;
	/* énum q */
	while (cpt < longueur_tab) {
		i = __builtin_ctz(cpt);
		id_tab ^= 1 << i;
		j = 0;
		while (j < int_par_ligne) {
			q[j] ^= base_quad.G[i*int_par_ligne + j];
			j += 1;
		}
		cpt2 = 1;
		memset(l, 0, int_par_ligne);
		/* énum l */
		while (cpt2 < limite) {
			i = __builtin_ctz(cpt2);
			j = 0;
			wt = 0;
			while (j < int_par_ligne) {
				l[j] ^= base_affine.G[i*int_par_ligne + j];
				wt += __builtin_popcountl(h[j] ^ q[j] ^ l[j]);
				j += 1;
			}
			if (wt > max) max = wt;
			cpt2 += 1;
		}
		tab[id_tab] = max;
		cpt += 1;
	}
	free_code64(base_quad);
	free_code64(base_affine);
	free(q);
	free(l);
	return tab;
}

int main(int argc, char *argv[]) {
	int ffdimen, ffsize, num, opt, job=0, module=1, val, rang_val;
	FILE *src;

	while ((opt = getopt(argc, argv, "n:f:")) != -1) {
		switch(opt) {
			case 'n':
				ffdimen = atoi(optarg);
				ffsize = 1 << ffdimen;
				break;
			case 'f':
				src = fopen(optarg, "r");
				break;
		}
	}

	uchar *f;
	uint64_t *h;
	int *tab;
	while ((f = load_boole(src, &num, ffsize))) {
		h = boole_to_int(f, ffsize);
		tab = tableau_poid_max(h, ffdimen, ffsize);
		printf("done\n");
	}
	free(h);
	return 0;
}
