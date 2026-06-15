#include <all.h>
#include "../include/include.h"
#include <omp.h>


int main(int argc, char *argv[]) {
	int ffdimen=7, ffsize=128, num, opt, k=2, job = 0, module = 1, target = 88;
	FILE *src;

	while ((opt = getopt(argc, argv, "k:n:f:m:j:t:")) != -1) {
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
			case 'j':
				job = atoi(optarg);
				break;
			case 'm':
				module = atoi(optarg);
				break;
			case 't':
				target = atoi(optarg);
				break;

		}
	}
	uchar *f;
	code tmp = RM(k, ffdimen);
	code64 c = code_to_code64(tmp);
	free_code(tmp);
	tmp = RMH(k, ffdimen);
	code64 code_homogene = code_to_code64(tmp);

	uint64_t *mot, *g;
	int *W, j, i;
	int int_par_ligne = (63+ffsize) / 64;
	uint64_t cpt=0, limite = (uint64_t) 1 << code_homogene.dim, indice_g = 0, indice_q;
	uint64_t limite2 = (uint64_t) 1 << c.dim;
	uint64_t limite1 = (uint64_t) 1 << ( ffdimen + 1 );
	int min, wt;
	time_t start, end;
	start = time(NULL);
	int* B = calloc( limite2, sizeof( int ) );    // base
	while ((f = load_boole(src, &num, ffsize))) {
		if (cpt % module == job) {
			mot = boole_to_int(f, ffsize);
			/* on stocke la valeur de wt(h + q) pour gagner du temps */
			W = tableau_poid(mot, c);
			/* on regarde tous les g dans le code homogène */

			for( indice_q = 0; indice_q < limite2; indice_q+=limite1 ) {
				int min = ffsize;
				for ( uint64_t l = 0; l < limite1; l++ ) 
					if ( W[ indice_q ^ l ] < min )  min = W[ indice_q ^ l ] ;
				B[ indice_q / limite1] = min;
			}

			for( indice_g = 0; indice_g < limite2; indice_g += limite1 ) {
				/* avec notre g on regarde W[q] + W[q+g] pour tous les q */
				indice_q = 0;
				wt = ffsize;

				while ( indice_q < limite2 &&  (wt  > target)  ) {
					int score = wt;
					int base = B[ indice_q / limite1 ];
					for ( uint64_t l = 0; l < limite1; l++ ) {
						int w = base + W[ indice_q^indice_g ^ l ];
						if ( w < score ){
							score = w;
						}
						if ( score > target ) 
							break;
					}
					wt = score;
					indice_q += limite1;
				}

				if (indice_q >= limite2) {
					{
						g = indice_to_boole(indice_g, c);
						uint64_t *boole_finale = merge(mot, g, ffsize);
						uchar *res = int_to_boole(boole_finale, ffsize<<1);
						print_anf(res, ffdimen + 1, ffsize<<1);
						free(boole_finale);
						free(res);
						free(g);
					}
				}
			}
			// puts("done");
			free(mot);
			free(f);
			free(W);
		}
		cpt += 1;
	}
	free(c.G);
	free(code_homogene.G);
	fclose(src);
	end = time(NULL);
	printf("#time = %ld\n", end-start);
	return 0;
}

