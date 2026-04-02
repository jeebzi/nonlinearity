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

int sup_walsh(uint64_t *f, int ffdimen, int ffsize) {
	/*
	 * prend une fonction booléenne et calcul la valeur absolu max de la transformé de Walsh de f
	 */
	int int_par_ligne = (ffsize + 63)/64;
	/* déclaration du code linéaire */
	code lin;
	lin = RMH(1, ffdimen);
	code64 base_lin = code_to_code64(lin);
	free_code(lin);
	uint64_t *l = calloc(int_par_ligne, sizeof(uint64_t));

	int maxi = 0, wt, j, i;
	int coef_walsh;

	unsigned int limite = (unsigned int) 1 << base_lin.dim, cpt = 1;
	while (cpt < limite) {
		i = __builtin_ctz(cpt);
		j = 0;
		wt = 0;
		while (j < int_par_ligne) {
			l[j] ^= base_lin.G[i*int_par_ligne + j];
			wt += __builtin_popcountl(l[j] ^ f[j]);
			j += 1;
		}
		coef_walsh = ffsize - (2 * wt);
		printf("walsh %d\n", coef_walsh);
		if (coef_walsh < 0) coef_walsh = -1 * coef_walsh;
		if (coef_walsh > maxi) maxi = coef_walsh;
		cpt += 1;
	}
	free(l);
	free(base_lin.G);
	return maxi;
}
