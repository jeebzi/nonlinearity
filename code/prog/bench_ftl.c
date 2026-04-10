#include <all.h>
#include "../include/include.h"

int main(int argc, char *argv[]) {
	int ffdimen, ffsize, opt, k, dist;
	FILE *src;

	while ((opt = getopt(argc, argv, "k:n:i:j:")) != -1) {
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
			case 't':
				target = atoi(optarg);
				break;



		}
	}
	code c = RM(k, ffdimen);
	uint64_t *words = code_to_int(c), *mot;
	uchar *f;
	while ((f = loaf_boole(src, &num, ffsize))) {
		mot = boole_to_int(f, ffsize);
		dist = distance_mot_code_min(mot, words, ffsize, c.dim, target);
