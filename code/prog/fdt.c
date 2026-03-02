#include <all.h>
#include "../include/include.h"

int main(int argc, char *argv[]) {
	int ffdimen, ffsize, num, opt, k, dist, target, job = 0, module = 1;
	FILE *src;

	while ((opt = getopt(argc, argv, "k:n:f:t:i:j:m:")) != -1) {
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

	int cpt = 0;
	srandom(time(NULL));
	code c = RM(k, ffdimen);
	code64 c1, c2;
	c1 = code_to_code64(c);
	free_code(c);
	c = RM(k - 1, ffdimen - 1);
	c2 = code_to_code64(c);
	free_code(c);

	uint64_t *mot;
	uchar *f;
	while ((f = load_boole(src, &num, ffsize))) {
		mot = boole_to_int(f, ffsize);
		if (cpt % module == job) {
			dist = distance_decode(mot, c1, c2, target, ffdimen, k);
			if (dist != -1) {
				printf("%d ", dist);
				print_anf(f, ffdimen, ffsize);
			}
		}
		cpt += 1;
		free(mot);
		free(f);
	}
	free(c1.G);
	free(c2.G);
	fclose(src);
	return 0;
}

