#include <all.h>
#include "../include/include.h"

int main(int argc, char *argv[]) {
	int ffdimen=7, ffsize=128, num, opt, k=2;
	FILE *src;

	while ((opt = getopt(argc, argv, "k:n:f:")) != -1) {
		switch(opt) {
			case 'k':
				k = atoi(optarg);
				break;
			case 'n':
				ffdimen = atoi(optarg);
				ffsize = 1 << ffdimen;
				break;
			case 'f':
				src = fopen(optarg, "r");
				break;
		}
	}
	uchar *g, *h;
	h = load_boole(src, &num, ffsize);
	g = load_boole(src, &num, ffsize);
	int int_par_ligne = (63+ffsize) / 64;
	int int_par_ligne1 = (63+(ffsize << 1)) / 64;
	uint64_t *boole_h, *boole_g, *boole_f;
	boole_h = calloc(int_par_ligne1, sizeof(uint64_t));
	boole_g = calloc(int_par_ligne1, sizeof(uint64_t));
	boole_f = calloc(int_par_ligne1, sizeof(uint64_t));
	int j;
	uint64_t *mot = boole_to_int(h, ffsize);
	j = 0;
	/* on construit boole_h = [h|h] */
	while (j < int_par_ligne1) {
		boole_h[j] = mot[j%int_par_ligne];
		j += 1;
	}
	free(mot);
	mot = boole_to_int(g, ffsize);
	j = 0;
	/* boole_g = [0|g] */
	while (j < int_par_ligne) {
		boole_g[j+int_par_ligne] = mot[j];
		j += 1;
	}
	free(mot);
	j = 0;
	while (j < int_par_ligne1) {
		boole_f[j] = boole_h[j] ^ boole_g[j];
		j += 1;
	}
	print_tab_uint64(boole_f, int_par_ligne1);
	

	code tmp = RM(2, 8);
	uint64_t *words = code_to_int(tmp);
	int dist;
	dist = distance_mot_code_min(boole_f, words, 1 << 8, tmp.dim, 0);
	printf("dist = %d\n", dist);
	return 0;
}


