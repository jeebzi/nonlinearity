#include <all.h>
#include "../include/include.h"

int main(int argc, char *argv[]) {
	int ffdimen, ffsize, num, opt, k, dist, target = -1, module = 1, job = 0; FILE *src;

	while ((opt = getopt(argc, argv, "k:n:f:t:m:j:")) != -1) {
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
			case 't':
				target = atoi(optarg);
				break;
			case 'm':
				module = atoi(optarg);
				break;
			case 'j':
				job = atoi(optarg);
				break;
		}
	}

	code c = RM(k, ffdimen+1);
	uint64_t *words = code_to_int(c), *mot_h, *mot_g;
	uchar *f, *h, *g;
	unsigned int cpt = 0;
	while ((h = load_boole(src, &num, ffsize))) {
		g = load_boole(src, &num, ffsize);
		if  (cpt % module == job) {
			mot_h = boole_to_int(h, ffsize);
			mot_g = boole_to_int(g, ffsize);
			uint64_t *mot_f = merge(mot_h, mot_g, ffsize);
			dist = distance_mot_code_min(mot_f, words, ffsize<<1, c.dim, target);
			if (dist != -1) {
				f = int_to_boole(mot_f, ffsize<<1);
				printf("%d ", dist);
				print_anf(f, ffdimen+1, ffsize<<1);
				free(f);
			}
			free(mot_h);
			free(mot_g);
			free(mot_f);
		}
		free(h);
		free(g);
		cpt += 1;
	}
	free_code(c);
	free(words);
	fclose(src);
	return 0;
}

