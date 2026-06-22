#include <all.h>
#include "../include/include.h"

int main(int argc, char *argv[]) {
	int ffdimen, num, ffsize, opt, k, dist, nb_sample=1024, target = -1, silence = 0, random = 0;
	FILE *src=NULL;

	while ((opt = getopt(argc, argv, "k:n:f:s:t:v:Sr")) != -1) {
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
			case 's':
				nb_sample = atoi(optarg);
				break;
			case 'S':
				silence = 1;
				break;
			case 'r':
				random = 1;
				break;



		}
	}
	code c;
	if (k == 1) c = RMH(k, ffdimen);
	else c = RM(k, ffdimen);
	struct timespec start, end;
	unsigned int iteration, cpt = 0;
	double time_moyen = 0, iter_moyen = 0, tim;
	int rejet;
	uint64_t *words = code_to_int(c), *mot;
	int tab_rejet[1024] = {0}, nb_accepte=0, nb_rejet=0;
	uchar *f;
	if (random == 0)
		while ((f = load_boole(src, &num, ffsize)) && cpt < nb_sample) {
			mot = boole_to_int(f, ffsize);
			clock_gettime(CLOCK_MONOTONIC, &start);
			dist = distance_mot_code_bench(mot, words, ffsize, c.dim, target, &iteration, &rejet);
			clock_gettime(CLOCK_MONOTONIC, &end);
			tim = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) * 1e-9;
			if (dist == -1) {
				nb_rejet += 1;
				tab_rejet[rejet] += 1;
			}
			else nb_accepte += 1;
			cpt += 1;
			iter_moyen = iter_moyen + (iteration - iter_moyen) / cpt;
			time_moyen = time_moyen + (tim - time_moyen) / cpt;
			free(mot);
			free(f);
		}
	else
		while(cpt < nb_sample) {
			mot = random_boole_int(ffsize);
			f = int_to_boole(mot, ffsize);
			free(f);
			clock_gettime(CLOCK_MONOTONIC, &start);
			dist = distance_mot_code_bench(mot, words, ffsize, c.dim, target, &iteration, &rejet);
			clock_gettime(CLOCK_MONOTONIC, &end);
			tim = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) * 1e-9;
			if (dist == -1) {
				nb_rejet += 1;
				tab_rejet[rejet] += 1;
			}
			else nb_accepte += 1;
			cpt += 1;
			iter_moyen = iter_moyen + (iteration - iter_moyen) / cpt;
			time_moyen = time_moyen + (tim - time_moyen) / cpt;
			free(mot);
		}
	if (silence == 0) {
		printf("target %d\n", target);
		print_distribution(tab_rejet, 1024);
		printf("nombre accepté : %d nombre rejeté : %d\n", nb_accepte, nb_rejet);
		printf("iter_moyen = %f\n", iter_moyen);
		printf("time_moyen = %f\n", time_moyen);
	}
	else {
		printf("%f\n", time_moyen);
	}
	if (src) fclose(src);
	free_code(c);
	free(words);
	return 0;
}
