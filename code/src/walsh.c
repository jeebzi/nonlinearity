#include "walsh.h"

void fourier_transform(int *boole, int ffsize) {
	/*
	 * effectue la tranformation de fourier rapide sur une fonction booléenne représenté en signe
	 */
	int nb_etape = __builtin_ctz(ffsize);
	int droite, gauche, i = 0, tmp, decalage, j;
	while (i < nb_etape) {
		decalage = 1 << i;
		gauche = 0;
		droite = decalage;
		j = 0;
		while (droite < ffsize) {
			tmp = boole[gauche];
			boole[gauche] = boole[gauche] + boole[droite];
			boole[droite] = tmp - boole[droite];
			j += 1;
			if (j >= decalage) {
				gauche += decalage + 1;
				droite = gauche + decalage;
				j = 0;
			}
			else {
				droite += 1;
				gauche += 1;
			}
		}
		i += 1;
	}
}

int* representation_signe(uchar *boole, int ffsize) {
	/*
	 * prend une fonction booléenne et la tranforme en représentation -1 ou 1
	 */
	int *res;
	res = (int*) calloc(ffsize, sizeof(int));
	int i = 0;
	while (i < ffsize) {
		if (boole[i] == 0) {
			res[i] = 1;
		}
		else
			res[i] = -1;
		i += 1;
	}
	return res;
}

