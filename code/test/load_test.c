#include "../include/include.h"

int main(int argc, char** argv) {
	int opt, ffsize, ffdimen, num;
	FILE *src;
	uchar *boole;
	while ((opt = getopt(argc, argv, "f:n:")) != -1) {
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

	boole = load_boole(src, &num, ffsize);
	print_anf(boole, ffdimen, ffsize);
	return 0;
}
