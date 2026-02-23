#include <all.h>
#include "../include/include.h"

int main(int argc, char *argv[]) {
	int opt, ffsize, ffdimen, num, k, dist;
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
			case 'k':
				k = atoi(optarg);
				break;
		}
	}
	
	boole = load_boole(src, &num, ffsize);
	c = RM(k, ffdimen);
	dist = calcule_distance_mot_code(c, boole, ffsize);
	printf("distance %d\n", dist);
	return 0;
}
	
