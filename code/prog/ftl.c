#include <all.h>
#include "../include/include.h"

int main(int argc, char *argv[]) {
	int ffdimen, ffsize, num, opt, k, dist, target, module = 1, job = 0;
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

	uint64_t *mot;
	int cpt = 0;
	uchar *f;
	while ((f = load_boole(src, &num, ffsize))) {
		if (cpt % module == job) {
			mot = boole_to_int(f, ffsize);
			dist = ftl(mot, ffdimen, ffsize, target);
			if (dist != -1) {
				printf("%d ", dist);
				print_anf(f, ffdimen, ffsize);
			}
			free(f);
			free(mot);
		}
		cpt += 1;
	}
	fclose(src);
	return 0;
}

