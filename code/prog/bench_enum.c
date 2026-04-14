#include <all.h>
#include "../include/include.h"

int main(int argc, char *argv[]) {
	int ffdimen, num, ffsize, opt, k, dist, nb_sample=1024, target = -1;
	FILE *src;

	while ((opt = getopt(argc, argv, "k:n:f:s:t:")) != -1) {
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



		}
	}
	code c = RM(k, ffdimen);
	time_t tim, start;
	unsigned int iteration, cpt = 0;
	double time_moyen = 0, iter_moyen = 0;
	int rejet;
	uint64_t *words = code_to_int(c), *mot;
	int tab_rejet[1024] = {0};
	uchar *f;
	while ((f = load_boole(src, &num, ffsize)) && cpt < nb_sample) {
		mot = boole_to_int(f, ffsize);
		start = time(NULL);
		dist = distance_mot_code_bench(mot, words, ffsize, c.dim, target, &iteration, &rejet);
		tim = time(NULL) - start;
		if (dist == -1) {
			tab_rejet[rejet] += 1;
		}
		cpt += 1;
		iter_moyen = iter_moyen + (iteration - iter_moyen) / cpt;
		time_moyen = time_moyen + (tim - time_moyen) / cpt;
		free(mot);
		free(f);
	}
	printf("target %d\n", target);
	print_distribution(tab_rejet, 1024);
	printf("iter_moyen = %f\n", iter_moyen);
	printf("time_moyen = %f\n", time_moyen);
	fclose(src);
	free_code(c);
	free(words);
	return 0;
}
