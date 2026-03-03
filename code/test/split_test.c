#include <all.h>
#include "../include/include.h"

int main(int argc, char *argv[]) {
	int opt, ffsize, ffdimen, num, k;
	FILE *src;
	uchar *boole;
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
		}
	}

	int int_par_ligne = (ffsize+63)/64;
	boole = load_boole(src, &num, ffsize);
	uint64_t *mot = boole_to_int(boole, ffsize);
	uint64_t **zip = split(mot, ffsize, int_par_ligne);
	print_tab_uint64(mot, int_par_ligne);
	print_tab_uint64(zip[0], int_par_ligne/2);
	print_tab_uint64(zip[1], int_par_ligne/2);
	return 0;
}

