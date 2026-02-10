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

	n = (ffsize+63) / 64;
	boole = load_boole(src, &num, ffsize);
	ptr_boole = boole_to_int(boole, ffsize);
	print_tab_uint64(ptr_boole, n);
	return 0;
}

