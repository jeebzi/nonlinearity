#include <all.h>
#include "../include/include.h"

int main(int argc, char *argv[]) {
	int ffdimen, ffsize, num, opt, k, module = 1, job = 0, cpt = 0;
	FILE *src;

	while ((opt = getopt(argc, argv, "k:n:f:m:j:")) != -1) {
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
			case 'm':
				module = atoi(optarg);
				break;
			case 'j':
				job = atoi(optarg);
				break;
		}
	}

	code c = RM(k, ffdimen);
	code64 c64 = code_to_code64(c);
	uint64_t *words = code_to_int(c), *mot;
	uchar *f;
	int orphan = 0;
	while ((f = load_boole(src, &num, ffsize))) {
		if (cpt % module == job) {
			mot = boole_to_int(f, ffsize);
			print_anf(f, ffdimen, ffsize);
			orphan = is_orphan(mot, c64, -1);
			if (orphan == 1) printf("is_orphan\n");
			else printf("not_orphan\n");
			orphan = 0;
			free(mot);
		}
		cpt += 1;
		free(f);
	}
	free(c64.G);
	free_code(c);
	free(words);
	fclose(src);
	return 0;
}

