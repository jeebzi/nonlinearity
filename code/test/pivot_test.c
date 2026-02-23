#include <all.h>
#include "../include/include.h"

int main(int argc, char *argv[]) {
	int opt, ffsize, ffdimen, num, k, dist, nb_tour = 10, target;
	FILE *src;
	uchar *boole;
	code c;
	while ((opt = getopt(argc, argv, "f:n:k:t:i:")) != -1) {
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
			case 't':
				target = atoi(optarg);
				break;
			case 'i':
				nb_tour = atoi(optarg);
				break;
		}
	}
	
	boole = load_boole(src, &num, ffsize);
	c = RM(k, ffdimen);
	dist = distance_probabiliste(c, boole, ffsize, nb_tour, target);
	printf("dist %d\n", dist);
	free_code(c);
	free(boole);
	fclose(src);
	return 0;
}

