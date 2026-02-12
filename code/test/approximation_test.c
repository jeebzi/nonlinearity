#include "../include/include.h"

int main(int argc, char *argv[]) {
	int opt, ffsize, ffdimen, num, k;
	FILE *src;
	uchar *boole;
	code c;
	while ((opt = getopt(argc, argv, "f:n:k:")) != -1) {
		switch(opt) {
			case 'f':
				src = fopen(optarg, "r");
				break;
			case 'n':
				ffdimen = atoi(optarg);
				ffsize = 1 << ffdimen;
				break;
			case 'k':
				k = atoi(optarg);
				break;
		}
	}
	c = RM(k, ffdimen);
	boole = load_boole(src, &num, ffsize);
	uint64_t *mot;
	mot = boole_to_int(boole, ffsize);
	liste_approximation(mot, c, 40);
	return 0;
	free(mot);
}

