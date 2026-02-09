#include "boole.h"

uchar* str_to_boole(char *s, int ffsize) {
	/*
	 * tranforem une chaine de charactère en fonvtion boléeenne représenter par tableau de uchar
	 */
	uchar *res;
	res = (uchar*) calloc(ffsize, sizeof(uchar));
	int u, x;
	while (*s != '=') s+= 1; //retirer la partie anf
	s += 1;
	while (*s) {
		u = 0;
		while (isalpha(*s)) {
			u |= 1 << (*s - 'a'); // on récuprer l'entier qui corespond au monôme
			s += 1;
		}
		// opération anf vers table de vérité
		x = 0;
		while (x < ffsize) {
			res[x] ^= ((u&x) == u);
			x += 1;
		}
		
		if (*s) s += 1;
	}
	return res;
}

uchar* load_boole(FILE *src, int *num, int ffsize) {
	/*
	 * charge depuis un pointeur vers fichier une fonction booléenne représenter par un tableau de u char
	 * num récupère la vanleur de la non linéarité de la fonction si elle est présente, -1 sinon
	 */
	uchar *res;
	char buffer[1024], *ptr;
	*num = -1;
	while (fgets(buffer, 1024, src)) {
		ptr = &buffer[0];
		if (sscanf(ptr, "%d", num) > 0) {
			res = str_to_boole(ptr, ffsize);
			return res;
		}
		if(*ptr != '#') {
			res = str_to_boole(buffer, ffsize);
			return res;
		}
	}
	return NULL;
}
