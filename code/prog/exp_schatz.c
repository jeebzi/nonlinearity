#include <all.h>
#include "../include/include.h"


int main(int argc, char *argv[]) {
	int ffdimen, ffsize, num, opt, k, *distribution;
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
	while (f = load_boole(src, &num, ffsize)) {
		print_anf(f, ffdimen, ffsize);
		free(f);
	}
	return 0;
}

