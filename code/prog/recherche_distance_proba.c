#include "../include/include.h"

int main(int argc, char *argv[]) {
	int ffdimen, ffsize, num, opt, k, dist, target, nb_tour = 100, job = 0, module = 1;
	FILE *src;

	while ((opt = getopt(argc, argv, "k:n:f:t:i:j:m:")) != -1) {
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
			case 'i':
				nb_tour = atoi(optarg);
				break;
			case 'm':
				module = atoi(optarg);
				break;
			case 'j':
				job = atoi(optarg);
				break;


		}
	}

	int cpt = 0;
	srandom(time(NULL));
	code c = RM(k, ffdimen);
	uchar *f;
	while ((f = load_boole(src, &num, ffsize))) {
		if (cpt % module == job) {
			dist = distance_probabiliste(c, f, ffsize, nb_tour, target);
			if (dist != -1) {
				printf("%d ", dist);
				print_anf(f, ffdimen, ffsize);
			}
		}
		cpt += 1;
		free(f);
	}
	free_code(c);
	fclose(src);
	return 0;
}

