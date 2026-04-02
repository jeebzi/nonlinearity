#include <all.h>
#include "../include/include.h"

int main(int argc, char *argv[]) {
	int opt, ffsize, ffdimen, num;
	FILE *src;
	uchar *boole;
	while ((opt = getopt(argc, argv, "f:n:k:")) != -1) {
		switch(opt) {
			case 'f':
				src = fopen(optarg, "r");
				break;
			case 'n':
				ffdimen = atoi(optarg);
				ffsize = 1 << ffdimen;
				break;
		}
	}

	boole = load_boole(src, &num, ffsize);

	uint64_t *mot;
	mot = boole_to_int(boole, ffsize);
	ftl(mot, ffdimen, ffsize, 64);
	free(mot);
	free(boole);
	fclose(src);
	return 0;
}


