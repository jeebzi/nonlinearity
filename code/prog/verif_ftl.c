#include <all.h>
#include "../include/include.h"

int main(int argc, char *argv[]) {
	int ffdimen, ffsize, num, opt, k, dist, dist2, target, module = 1, job = 0;
	FILE *src;

	while ((opt = getopt(argc, argv, "k:n:f:t:m:j:")) != -1) {
		switch(opt) {
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

	code c = RM(2, ffdimen);
	uint64_t *words = code_to_int(c);
	uint64_t *mot;
	int cpt = 0;
	uchar *f;
	while ((f = load_boole(src, &num, ffsize))) {
		if (cpt % module == job) {
			mot = boole_to_int(f, ffsize);
			dist = ftl(mot, ffdimen, ffsize, target);
			dist2 = distance_mot_code_min(mot, words, ffsize, c.dim, target);
			printf("%d %d ", dist, dist2);
			print_anf(f, ffdimen, ffsize);
			assert(dist == dist2);
			free(f);
			free(mot);
		}
		cpt += 1;
	}
	free(words);
	fclose(src);
	return 0;
}

