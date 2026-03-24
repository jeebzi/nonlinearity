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
	print_tab_uchar(boole, ffsize);
	char* sboole;
	sboole = representation_signe(boole, ffsize);
	fourrier_transform(sboole, ffsize);
	print_tab_char(sboole, ffsize);
	free(boole);
	free(sboole);
	return 0;
}
