#include "../src/all.h"

int main() {
	int ffdimen = 3;
	int ffsize = 1 << ffdimen;
	link_list_uint *L = NULL;
	L = cherche_non_triviaux(ffdimen, ffsize);
	print_list_uint(L);
	return 0;
}
