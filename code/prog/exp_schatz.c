#include <all.h>
#include "../include/include.h"


int main(int argc, char *argv[]) {
	int ffdimen, ffsize, num, opt, k;
	FILE *src;

	while ((opt = getopt(argc, argv, "k:n:f:")) != -1) {
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
		}
	}
	uchar *f;
	code tmp = RM(k, ffdimen);
	code64 c = code_to_code64(tmp);
	free_code(tmp);
	tmp = RMH(k, ffdimen);
	code64 code_homogene = code_to_code64(tmp);

	uchar *g_boole;
	uint64_t *mot;
	int *W, j, i;
	int int_par_ligne = (63+ffsize) / 64;
	uint64_t cpt, limite = (uint64_t) 1 << code_homogene.dim, indice_g = 0, indice_q;
	uint64_t *g = calloc(int_par_ligne, sizeof(uint64_t));
	uint64_t limite2 = (uint64_t) 1 << c.dim;
	int min, wt;
	while ((f = load_boole(src, &num, ffsize))) {
		mot = boole_to_int(f, ffsize);
		/* on stocke la valeur de wt(h + q) pour gagner du temps */
		W = tableau_poid(mot, c);
		/* on regarde tous les g dans le code homogène */
		memset(g, 0, int_par_ligne*sizeof(uint64_t));
		cpt = 1;
		while(cpt < limite) {
			i = __builtin_ctzl(cpt);
			indice_g ^= (uint64_t) 1 << i;
			j = 0;
			while (j < int_par_ligne) {
				g[j] ^= c.G[i * int_par_ligne + j];
				j += 1;
			}
			/* avec notre g on regarde W[q] + W[q+g] pour tous les q */
			indice_q = 0;
			min = W[indice_q]<<1;
			wt = W[indice_q] + W[indice_q^indice_g];
			while (indice_q < limite2 && ((wt) > 88)) {
				if (wt < min) min = wt;
				indice_q += 1;
				wt = W[indice_q] + W[indice_q^indice_g];
			}
			if (indice_q >= limite) {
				printf("h : ");
				print_anf(f, ffdimen, ffsize);
				printf("g : ");
				g_boole = int_to_boole(g, ffsize);
				print_anf(g_boole, ffdimen, ffsize);
				free(g_boole);
				printf("min = %d\n", min);
			}
			cpt += 1;
		}
		free(mot);
		free(f);
		free(W);
	}
	free(c.G);
	free(code_homogene.G);
	fclose(src);
	return 0;
}

