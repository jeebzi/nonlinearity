#include <all.h>
#include "../include/include.h"

int main(int argc, char *argv[]) {
	int job, ffdimen, ffsize, opt, k, dist, nb_iter;

	while ((opt = getopt(argc, argv, "k:n:i:j:")) != -1) {
		switch(opt) {
			case 'k':
				k = atoi(optarg);
				break;
			case 'n':
				ffdimen = atoi(optarg);
				ffsize = 1 << ffdimen;
				break;
			case 'i':
				nb_iter = atoi(optarg);
				break;
			case 'j':
				job = atoi(optarg);
				break;



		}
	}


	srandom(time(NULL) ^ job);
	int cpt = 0;
	time_t start, end;
	code c = RM(k, ffdimen);
	code64 c1, c2;
	c1 = code_to_code64(c);
	uint64_t *c_int = code_to_int(c);
	free_code(c);
	c = RM(k, ffdimen - 1);
	c2 = code_to_code64(c);
	free_code(c);

	uint64_t *mot;
	uchar *f;
	while (cpt < nb_iter) {
		f = random_boole(ffdimen, -1);
		mot = boole_to_int(f, ffsize);
		print_anf(f, ffdimen, ffsize);
		//calcul sans opti
		start = time(NULL);
		dist = distance_mot_code_min(mot, c_int, ffsize, c1.dim, 0);
		end = time(NULL);
		printf("%lu sec dist: %d", end-start, dist);


		start = time(NULL);
		dist = distance_decode(mot, c1, c2, 0, ffdimen, k);
		end = time(NULL);
		printf("%lu sec optimisé dist: %d\n", end-start, dist);
		cpt += 1;
		free(mot);
		free(f);
	}
	free(c_int);
	free(c1.G);
	free(c2.G);
	return 0;
}

