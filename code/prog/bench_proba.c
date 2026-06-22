#include <all.h>
#include "../include/include.h"

int main(int argc, char *argv[]) {
	int ffdimen, ffsize, num, opt, k, dist, target, nb_tour = 100, job = 0, module = 1, nb_sample=1024;
	FILE *src;

	while ((opt = getopt(argc, argv, "k:n:f:t:i:j:m:s:")) != -1) {
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
			case 's':
				nb_sample=atoi(optarg);
				break;


		}
	}

	double time_moyen = 0, tim;
	struct timespec start, end;
	int cpt = 0;
	srandom(time(NULL));
	code c = RM(k, ffdimen);
	uchar *f;
	while ((f = load_boole(src, &num, ffsize)) && cpt < nb_sample) {
		if (cpt % module == job) {
			clock_gettime(CLOCK_MONOTONIC, &start);
			dist = distance_probabiliste(c, f, ffsize, nb_tour, target);
			clock_gettime(CLOCK_MONOTONIC, &end);
			tim = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) * 1e-9;
			if (dist != -1) {
				printf("%d ", dist);
				print_anf(f, ffdimen, ffsize);
			}
		}
		cpt += 1;
		time_moyen = time_moyen + (tim - time_moyen) / cpt;
		free(f);
	}
	printf("target %d\n", target);
	printf("time_moyen = %f\n", time_moyen);
	free_code(c);
	fclose(src);
	return 0;
}

