#include "non_trivial.h"

link_list_uint cherche_non_triviaux(int ffdimen, int ffsize) {
	/*
	 * donne la liste de tous les x, y, z, t dans F_2^m tel que pour tous les q dans les fonctions
	 * quadratiques homogène q(x) + q(y) + q(z) + q(t) = 0 avec x < y < z < t
	 */
	link_list_uint = res;
	unsigned int x, y, z, t;

	//allocation mémoire
	int int_par_ligne = (ffsize+63)/64;
	x = (uint64_t*) calloc(int_par_ligne, sizeof(uint64_t));
	y = (uint64_t*) calloc(int_par_ligne, sizeof(uint64_t));
	z = (uint64_t*) calloc(int_par_ligne, sizeof(uint64_t));
	t = (uint64_t*) calloc(int_par_ligne, sizeof(uint64_t));
	//initialisation il faut que x < y < z < t
	y[0] = 1;
	z[0] = 2;
	t[0] = 3;

	while (x <= ffsize - 3) {
		while (y <= ffsize - 2) {
			while (z <= ffsize - 1) {
				while (t <= ffsize) {
					flag = check_non_trivial(x, y, z, t, ffdimen, ffsize);
					if (flag == 1) {
						add_list_uint64(res, x);
						add_list_uint64(res, y);
						add_list_uint64(res, z);
						add_list_uint64(res, t);
					}
					t += 1;
				}
				z += 1;
				t = z + 1;
			}
			y += 1;
			z = y + 1;
			t = z + 1;
		}
		x += 1;
		y = x + 1;
		z = y + 1;
		t = z + 1;
	}
	return res;

}

int check_non_trivial(unsigned int x, unsigned int y, unsigned z, unsigned int t, int ffdimen, int ffsize) {
	/*
	 * prend 4 vecteurs dans F_2^m et regarde si pour tous les q dans RMH(2, m)
	 * q(x) + q(y) + q(z) + q(t) = 0
	 * renvoie 1 si c'est vrai 0 sinon
	 */
	res = 0;

}
