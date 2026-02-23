#include <all.h>
#include "../include/include.h"

int main(int argc, char *argv[]) {
	int opt, ffsize, ffdimen, num, k, n;
	FILE *src;
	uchar *boole;
	uint64_t *ptr_boole;
	code c;
	while ((opt = getopt(argc, argv, "f:n:k:")) != -1) {
		switch(opt) {
			case 'f':
				src = fopen(optarg, "r");
				break;
			case 'n':
				ffdimen = atoi(optarg);
				ffsize = 1 << ffdimen;
				break;
			case 'k':
				k = atoi(optarg);
				break;
		}
	}
	c = RM(k, ffdimen);
	int int_par_ligne = (c.longueur+63) / 64;
	uint64_t *words;
	words = code_to_int(c);
	print_tab_uint64(words, c.dim*int_par_ligne);
	return 0;
}

