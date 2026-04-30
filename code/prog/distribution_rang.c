#include <all.h>
#include "../include/include.h"

int main(int argc, char *argv[]) {
	int ffdimen, ffsize, num, opt, job=0, module=1, val, rang_val;
	FILE *src;

	while ((opt = getopt(argc, argv, "k:n:f:j:m:t:")) != -1) {
		switch(opt) {
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
		}
	}

	unsigned char *boole;
	uint64_t *mot;
	num = 0;
	int *distribution;
	distribution = (int*) calloc(ffdimen+1, sizeof(int));
	while ((boole = load_boole(src, &val, ffsize))) {
		if (num % module == job) {
			mot = boole_to_int(boole, ffsize);
			rang_val = rang(mot, ffdimen, ffsize);
			distribution[rang_val] += 1;
			free(mot);
		}
		free(boole);
		num += 1;
	}
	print_distribution(distribution, ffdimen);
	free(distribution);
	fclose(src);
	return 0;
}
	
