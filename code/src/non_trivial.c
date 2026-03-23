#include "non_trivial.h"

link_list_uint* cherche_non_triviaux(int ffdimen, int ffsize) {
	/*
	 * donne la liste de tous les x, y, z, t dans F_2^m tel que pour tous les q dans les fonctions
	 * quadratiques homogène q(x) + q(y) + q(z) + q(t) = 0 avec x < y < z < t
	 */
	link_list_uint* res = NULL;
	unsigned int x, y, z, t;

	//allocation mémoire
	int flag;
	//initialisation il faut que x < y < z < t
	x = 0;
	y = 1;
	z = 2;
	t = 3;

	while (x < ffsize - 3) {
		while (y < ffsize - 2) {
			while (z < ffsize - 1) {
				while (t < ffsize) {
					flag = check_non_trivial(x, y, z, t, ffdimen);
					if (flag == 1) {
						res = add_list_uint(res, t);
						res = add_list_uint(res, z);
						res = add_list_uint(res, y);
						res = add_list_uint(res, x);
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

int check_non_trivial(unsigned int x, unsigned int y, unsigned z, unsigned int t, int ffdimen) {
	/*
	 * prend 4 vecteurs dans F_2^m et regarde si pour tous les q dans RMH(2, m)
	 * q(x) + q(y) + q(z) + q(t) = 0
	 * renvoie 1 si c'est vrai 0 sinon
	 */
	/* stratégie:
	 * regarder toutes les formes x_ij et regarder si elles sont toutes égale à 0 si une est égale à 1 c'est impossible
	 * que pour tous les q dans RMH(2, m) que q(x) + q(y) + q(z) + q(t) = 0
	 */
	int res;
	int i = 0, j;
	while (i < ffdimen - 1) {
		j = i + 1;
		while (j < ffdimen) {
			res = condition_non_trivial(x, y, z, t, i, j);
			if (res == 0) return 0;
			j += 1;
		}
		i += 1;
	}
	return 1;


}

int condition_non_trivial(unsigned int x, unsigned int y, unsigned int z, unsigned int t, int i, int j) {
	int res = 0;
	res |= ((x >> i) & 1) && ((x >> j) & 1);
	res |= ((y >> i) & 1) && ((y >> j) & 1);
	res |= ((z >> i) & 1) && ((z >> j) & 1);
	res |= ((t >> i) & 1) && ((t >> j) & 1);
	if (res == 0) {return 1; }
	return 0;
}

int affiche_non_trivial(link_list_uint *L) {
	/*
	 * prend une liste chaîné avec toutes les solutions des non triviaux et les affiches
	 * renvoie le nombre d solution
	 */
	int nb_solution = 0;
	int cpt = 0;
	while (L != NULL) {
		printf("%u ", L->val);
		if (cpt == 3) {
			nb_solution += 1;
			printf("\n");
		}
		cpt = (cpt + 1) % 4;
		L = L->next;
	}
	return nb_solution;
}
