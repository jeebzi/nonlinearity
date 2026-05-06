#include <all.h>
#include "../include/include.h"
#include <omp.h>


int main(int argc, char *argv[]) {
	int ffdimen=7, ffsize=128, num, opt, k=2, core=omp_get_num_procs();
	FILE *src;

	while ((opt = getopt(argc, argv, "k:n:f:c:")) != -1) {
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
			case 'c':
				core = atoi(optarg);
				break;
		}
	}
	uchar *f;
	code tmp = RM(k, ffdimen);
	code64 c = code_to_code64(tmp);
	free_code(tmp);
	tmp = RMH(k, ffdimen);
	code64 code_homogene = code_to_code64(tmp);

	uchar *g_boole;
	uint64_t *mot, *g;
	int *W, j, i;
	int int_par_ligne = (63+ffsize) / 64;
	uint64_t cpt, limite = (uint64_t) 1 << code_homogene.dim, indice_g = 0, indice_q;
	uint64_t limite2 = (uint64_t) 1 << c.dim;
	uint64_t limite1 = (uint64_t) 1 << ( ffdimen + 1 );
	int min, wt;
	time_t start, end;
	start = time(NULL);
	while ((f = load_boole(src, &num, ffsize))) {
		mot = boole_to_int(f, ffsize);
		/* on stocke la valeur de wt(h + q) pour gagner du temps */
		W = tableau_poid(mot, c);
		/* on regarde tous les g dans le code homogène */
		omp_set_num_threads(core);
		#pragma omp parallel for private(indice_q, wt) schedule(dynamic)
		for( indice_g = 0; indice_g < limite2; indice_g += limite1 ) {
			/* avec notre g on regarde W[q] + W[q+g] pour tous les q */
			indice_q = 0;
			wt = ffsize;

			while ( indice_q < limite2 &&  (wt  > 88)  ) {
				int score = wt;
				int base = W[indice_q];
				for ( uint64_t l = 0; l < limite1; l++ ) {
					int w = base + W[ indice_q^indice_g ^ l ];
					if ( w < score ){
					       	score = w;
					}
				}
				wt = score;
				indice_q += limite1;
			}
					
			if (indice_q >= limite2) {
				#pragma omp critical 
				{
				printf("h : ");
				print_anf(f, ffdimen, ffsize);
				printf("g : ");
				g = indice_to_boole(indice_g, c);
				g_boole = int_to_boole(g, ffsize);
				print_anf(g_boole, ffdimen, ffsize);
				free(g_boole);
				free(g);
				 }
			}
		}
		// puts("done");
		free(mot);
		free(f);
		free(W);
	}
	free(c.G);
	free(code_homogene.G);
	fclose(src);
	end = time(NULL);
	printf("#time = %ld\n", end-start);
	return 0;
}

