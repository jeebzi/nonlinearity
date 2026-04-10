#include "bench.h"
int distance_mot_code_bench(uint64_t *mot, uint64_t *base, uint64_t ffsize, int nb_ligne, int target, unsigned int *iter, int *rejet) {
	/*
	 * effectue le calcule de non linéarité d'une fonction booléenne. Renvoie en plus le nombre d'itération et la valeur
	 * de la distance lors du rejet
	 */
	*iter = 0; *rejet = -1;
	int int_par_ligne = (ffsize+63) / 64;
	int score = weight_64(mot, int_par_ligne);
	uint64_t limite = (uint64_t)1 << nb_ligne;
	uint64_t cpt = 1;
	int i; // indice bit qui change
	int j, wt;
	while (cpt < limite) {
		*iter += 1;
		i = __builtin_ctzl(cpt);
		//addition entre mot dans F2
		j = 0;
		wt = 0;
		while (j < int_par_ligne) {
			mot[j] ^= base[i*int_par_ligne + j];
			wt += __builtin_popcountl(mot[j]);
			j += 1;
		}
		if (wt < target){ *rejet = wt; return -1;}
		if (wt < score) score = wt;
		cpt += 1;
	}
	return score;
}

unsigned int ftl_bench(uint64_t *f, int ffdimen, int ffsize, int target, unsigned int *iter, int *rejet) {
	/*
	 */
	assert(ffdimen >= 7);
	assert(ffsize == (1 << ffdimen));

	*iter = 0; *rejet = - 1;
	int int_par_ligne = (ffsize+63)/64;
	int int_par_ligne2 = ((ffsize >> 1) + 63) / 64;
	int j, i, k, over = 0, wt;
	unsigned int score = 0;
	code tmp;
	tmp = RMH(2, ffdimen-1);
	code64 base_quad = code_to_code64(tmp);
	free_code(tmp);
	tmp = RMH(1, ffdimen-1);
	code64 base_lin = code_to_code64(tmp);
	free_code(tmp);

	uint64_t *p; /* prefix de q dans rm(2,8) */
	uint64_t *l, *y, *fpp;
	p = calloc(int_par_ligne2, sizeof(uint64_t));
	l = calloc(int_par_ligne, sizeof(uint64_t));
	y = calloc(int_par_ligne, sizeof(uint64_t));
	fpp = calloc(int_par_ligne, sizeof(uint64_t));

	uint64_t lim_quad, cpt_quad, lim_lin, cpt_lin;
	lim_quad = (uint64_t) 1 << base_quad.dim;
	lim_lin = (uint64_t) 1 << base_lin.dim;
	cpt_quad = 0;

	/*restriction f0 f1 */
	uint64_t *f0, *f1, **zip;
	zip = split(f, ffsize, int_par_ligne);
	f0 = zip[0];
	f1 = zip[1];
	free(zip);
	/* variable pour stocker f0 + P et f1 + P */
	uint64_t *f0p, *f1p;
	f0p = calloc(int_par_ligne2, sizeof(uint64_t));
	f1p = calloc(int_par_ligne2, sizeof(uint64_t));
	unsigned int gamma0, gamma1, gamma;
	while (over == 0 && cpt_quad < lim_quad) {
		if (cpt_quad == 0) {
			gamma0 = sup_walsh(f0, ffdimen - 1, ffsize >> 1);
			gamma1 = sup_walsh(f1, ffdimen - 1, ffsize >> 1);
		}
		else {
			i = __builtin_ctzl(cpt_quad);
			j = 0;
			while (j < int_par_ligne2) {
				p[j] ^= base_quad.G[i*int_par_ligne2 + j];
				f0p[j] = p[j] ^ f0[j];
				f1p[j] = p[j] ^ f1[j];
				j += 1;
			}
			gamma0 = sup_walsh(f0p, ffdimen - 1, ffsize >> 1);
			gamma1 = sup_walsh(f1p, ffdimen - 1, ffsize >> 1);
		}
		// printf("gamma0 %d + gamma 1 %d = %d\n",gamma0, gamma1, gamma0 + gamma1);
		if ((gamma0 + gamma1) >= score) {
			*iter += 1;
			memset(l, 0, int_par_ligne);
			cpt_lin = 0;
			while (over == 0 && cpt_lin < lim_lin) {
				if (cpt_lin == 0) {
					/* création de f + p  avec p sur m + 1 variable [p|p]*/
					j = 0;
					while (j < int_par_ligne) {
						fpp[j] = f[j] ^ p[j%int_par_ligne2];
						y[j] = fpp[j];
						j += 1;
					}
				}
				/* on regarde y = f + p + x_8l */
				else {
					i = __builtin_ctzl(cpt_lin);
					j = 0;
					k = int_par_ligne2;
					/* l = [0|l] */
					while (j < int_par_ligne2) {
						l[k] ^= base_lin.G[i*int_par_ligne2 + j];
						y[k] = fpp[k] ^ l[k];
						k += 1;
						j += 1;
					}
				}
				gamma = sup_walsh(y, ffdimen, ffsize);
				if (gamma > score) {
					score = gamma;
					wt = (ffsize >> 1) - (score >> 1);
					if (wt < target){ *rejet = wt; over = 1;}
				}
				cpt_lin += 1;
			}
		}
		cpt_quad += 1;
		// printf("cpt_quad %lu lim %lu\n", cpt_quad, lim_quad);
	}


	free(l);
	free(p);
	free(base_quad.G);
	free(base_lin.G);
	free(f0p);
	free(f1p);
	free(f0);
	free(f1);
	free(fpp);
	free(y);
	if (over == 1) return -1;
	return score;
}
