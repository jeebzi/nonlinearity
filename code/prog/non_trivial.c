#include <all.h>
#include "../include/include.h"

int main(int argc, char *argv[]) {
	int ffdimen, ffsize, opt;

	while ((opt = getopt(argc, argv, "n:")) != -1) {
		switch(opt) {
			case 'n':
				ffdimen = atoi(optarg);
				ffsize = 1 << ffdimen;
				break;
		}
	}

	int nb;
	link_list_uint *L = NULL;
	L = cherche_non_triviaux(ffdimen, ffsize);
	nb = affiche_non_trivial(L);
	printf("#nb solution: %d\n", nb);
	return 0;
}

