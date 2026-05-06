#include <all.h>
#include "../include/include.h"

int main(int argc, char *argv[]) {
	int opt, ffsize, ffdimen, num, k, n;
	FILE *src;
	uchar *boole;
	uint64_t *ptr_boole;
	while ((opt = getopt(argc, argv, "f:n:k:")) != -1) {
		switch(opt) {
			case 'n':
				ffdimen = atoi(optarg);
				ffsize = 1 << ffdimen;
				break;
			case 'k':
				k = atoi(optarg);
				break;
		}
	}


	int int_par_ligne = (63 + ffsize) / 64;
	code tmp = RM(k, ffdimen);
	code64 c = code_to_code64(tmp);
	uint64_t *g = calloc(int_par_ligne, sizeof(uint64_t));
	uint64_t *g_bis;
	int j, i, indice = 0;
	uint64_t cpt = 1, limite = (uint64_t)1 << c.dim;
	while (cpt < limite) {
		i = __builtin_ctzl(cpt);
		indice ^= (1 << i);
		j = 0;
		while (j < int_par_ligne) {
			g[j] ^= c.G[i*int_par_ligne + j];
			j += 1;
		}
		g_bis = indice_to_boole(indice, c);
		print_tab_uint64(g, int_par_ligne);
		print_tab_uint64(g_bis, int_par_ligne);
		free(g_bis);
		cpt += 1;
		printf("\n");
	}
	return 0;
}
