#include <all.h>

int main(int argc, char *argv[]) {
	int opt, ffsize, ffdimen, num;
	FILE *src;
	uchar *boole;
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
	boole = load_boole(src, &num, ffsize);
	uint64_t *f = boole_to_int(boole, ffsize);
	int max;
	print_tab_uchar(boole, ffsize);
	int* sboole;
	sboole = representation_signe(boole, ffsize);
	fourier_transform(sboole, ffsize);
	print_tab_int(sboole, ffsize);
	fourier_transform(sboole, ffsize);
	print_tab_int(sboole, ffsize);
	max = sup_walsh(f, ffdimen, ffsize);
	printf("max walsh = %d\n", max);
	free(f);
	free(boole);
	free(sboole);
	return 0;
}
