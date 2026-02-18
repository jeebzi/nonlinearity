#include "../include/include.h"

int main(int argc, char *argv[]) {
	int ffdimen, ffsize, num, opt, k, target, job=0, module=1, val;
	FILE *src;

	while ((opt = getopt(argc, argv, "k:n:f:j:m:t:")) != -1) {
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
			case 'j':
				job = atoi(optarg);
				break;
			case 'm':
				module = atoi(optarg);
				break;
			case 't':
				target = atoi(optarg);
				break;
		}
	}

	unsigned char *boole;
	uint64_t *mot;
	code c = RM(k, ffdimen);
	num = 0;
	while ((boole = load_boole(src, &val, ffsize))) {
		if (num % module == job) {
			mot = boole_to_int(boole, ffsize);
			liste_approximation(mot, c, target);
			free(mot);
		}
		free(boole);
		num += 1;
	}
	fclose(src);
	free_code(c);
	return 0;
}
	
