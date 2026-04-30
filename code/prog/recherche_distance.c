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

	code c = RM(k, ffdimen);
	uint64_t *words = code_to_int(c), *mot;
	uchar *f;
	unsigned int cpt = 0;
	while ((f = load_boole(src, &num, ffsize))) {
		if  (cpt % module == job) {
			mot = boole_to_int(f, ffsize);
			dist = distance_mot_code_min(mot, words, ffsize, c.dim, target);
			if (dist != -1) {
				 printf("%d ", dist);
				 print_anf(f, ffdimen, ffsize);
			}
			free(f);
			free(mot);
		}
		cpt += 1;
	}
	free_code(c);
	free(words);
	fclose(src);
	return 0;
}

