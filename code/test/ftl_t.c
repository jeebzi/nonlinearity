#include <all.h>
#include "../include/include.h"

int main(int argc, char *argv[]) {
	int opt, ffsize, ffdimen, num, target;
	FILE *src;
	uchar *boole;
	while ((opt = getopt(argc, argv, "f:n:k:t:")) != -1) {
		switch(opt) {
			case 'f':
				src = fopen(optarg, "r");
				break;
			case 'n':
				ffdimen = atoi(optarg);
				ffsize = 1 << ffdimen;
				break;
			case 't':
				target = atoi(optarg);
				break;
		}
	}

	boole = load_boole(src, &num, ffsize);

	uint64_t *mot;
	int dist;
	mot = boole_to_int(boole, ffsize);
	dist = ftl(mot, ffdimen, ffsize, 80);
	printf("dist = %d\n", dist);
	free(mot);
	free(boole);
	fclose(src);
	return 0;
}


