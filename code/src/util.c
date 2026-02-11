#include "util.h"

uint64_t* copy_uint64(uint64_t *src, int n) {
	/*
	 * copy n élément d'un tableau de uint64
	 */
	uint64_t *dst;
	dst = (uint64_t*) malloc(n*sizeof(uint64_t));

	int i = 0;
	while (i < n) {
		dst[i] = src[i];
		i += 1;
	}
	return dst;
}
