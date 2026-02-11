#include "../include/include.h"


int main(int argc, char *argv[]) {
	int ffdimen, ffsize, num, opt, k, *distribution;
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

	code c = RM(k, ffdimen);
	uint64_t *words = code_to_int(c), *mot;
	uchar *f;
	while ((f = load_boole(src, &num, ffsize))) {
		print_anf(f, ffdimen, ffsize);
		mot = boole_to_int(f, ffsize);
		distribution = distribution_distance(mot, words, ffsize, c.dim);
		print_distribution(distribution, ffsize);
	}
	free_code(c);
	free(words);
	free(mot);
	free(f);
	return 0;
}

