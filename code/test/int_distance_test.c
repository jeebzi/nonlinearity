#include <all.h>
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

	boole = load_boole(src, &num, ffsize);
	c = RM(k, ffdimen);

	uint64_t *mot, *words;
	mot = boole_to_int(boole, ffsize);
	words = code_to_int(c);
	int dist;
	dist = distance_mot_code_zip(mot, words, ffsize, c.dim);
	printf("distance %d\n", dist);
	return 0;
}


