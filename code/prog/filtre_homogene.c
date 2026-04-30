#include <all.h>
#include "../include/include.h"


/*
 * programme pour prendre un fichier de fonction booléenne et garder que les fonctions homogène
 */

int main(int argc, char *argv[]) {
	int ffdimen, ffsize, num, opt, k = -1, job=0, module=1, val;
	FILE *src;

	while ((opt = getopt(argc, argv, "k:n:f:j:m:")) != -1) {
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
		}
	}

	unsigned char *boole;
	int homog;
	num = 0;
	while ((boole = load_boole(src, &val, ffsize))) {
		if (num % module == job) {
			homog = is_homogene(boole, k, ffsize);
			if (homog == 1) {
				if (val != -1) printf("%d ", val);
				print_anf(boole, ffdimen, ffsize);
			}
		}
		free(boole);
		num += 1;
	}
	fclose(src);
	return 0;
}
	
