#include "../include/include.h"

int main(int argc, char *argv[]) {
	int ffdimen, ffsize, num, opt, k, dist, target;
	FILE *src;

	while ((opt = getopt(argc, argv, "k:n:f:t:")) != -1) {
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
		}
	}

	code c = RM(k, ffdimen);
	uint64_t *words = code_to_int(c), *mot;
	uchar *f;
	while ((f = load_boole(src, &num, ffsize))) {
		mot = boole_to_int(f, ffsize);
		dist = distance_mot_code_zip(mot, words, ffsize, c.dim);
		if (dist == target) print_anf(f, ffdimen, ffsize);
	}
	free_code(c);
	free(words);
	free(mot);
	free(f);
	return 0;
}

