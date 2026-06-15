#include <all.h>
#include "../include/include.h"

int main(int argc, char *argv[]) {
	int ffdimen, num, ffsize, opt, dist, nb_sample=1024, random = 0;
	FILE *src=NULL;

	while ((opt = getopt(argc, argv, "n:f:s:r")) != -1) {
		switch(opt) {
			case 'n':
				ffdimen = atoi(optarg);
				ffsize = 1 << ffdimen;
				break;
			case 'f':
				src = fopen(optarg, "r");	
				break;
			case 's':
				nb_sample = atoi(optarg);
				break;
			case 'r':
				random = 1;
				break;



		}
	}
	struct timespec start, end;
	unsigned int iteration, cpt = 0;
	double time_moyen = 0, iter_moyen = 0, tim;
	int *signe;
	uint64_t *mot;
	uchar *f;
	if (random == 0)
		while ((f = load_boole(src, &num, ffsize)) && cpt < nb_sample) {
			signe = representation_signe(f, ffsize);
			clock_gettime(CLOCK_MONOTONIC, &start);
			dist = non_linearite_walsh(signe, ffsize);
			clock_gettime(CLOCK_MONOTONIC, &end);
			tim = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) * 1e-9;
			cpt += 1;
			time_moyen = time_moyen + (tim - time_moyen) / cpt;
			free(f);
			free(signe);
		}
	else
		while(cpt < nb_sample) {
			/* pour la génération aléatoire on génére d'abord une fonction avec
			 * la méthiode de représentation en entier pouis on converti en tableau uchar puis
			 * en signe
			 */
			mot = random_boole_int(ffsize);
			f = int_to_boole(mot, ffsize);
			free(mot);
			signe = representation_signe(f, ffsize);

			clock_gettime(CLOCK_MONOTONIC, &start);
			dist = non_linearite_walsh(signe, ffsize);
			clock_gettime(CLOCK_MONOTONIC, &end);
			tim = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) * 1e-9;
			cpt += 1;
			time_moyen = time_moyen + (tim - time_moyen) / cpt;
			free(f);
			free(signe);
		}
	printf("%f\n", time_moyen);
	if (src) fclose(src);
	return 0;
}
