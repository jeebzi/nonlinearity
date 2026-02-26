#include "../include/include.h"
#include <all.h>

int check_poid_spec(int wt) {
	switch(wt) {
		case 56:
			return 1;
		case 60:
			return 1;
		case 64:
			return 1;
		case 68:
			return 1;
		case 72:
			return 1;
	}
	return 0;
}


int enum_spec_2_4_7(uint64_t *mot, uint64_t *base, int ffdimen, int nb_ligne, int int_par_ligne) {
	/*
	 * calcule le nombre de q appartenant au code générer par base vérifiant mot + q est une
	 * fonction avec le spec qu'on veut
	 */
	int res = 0;	
	uint64_t *q, *fq, *fql;
	q = (uint64_t*) calloc(int_par_ligne*nb_ligne, sizeof(uint64_t));

	// code lineaire
	code code_lin;
	code_lin = RMH(1, ffdimen);
	uint64_t *base_lin = code_to_int(code_lin), *l;

	//énum de tout les q
	int cpt = 1, cpt2;
	uint64_t limite = (uint64_t)1 << nb_ligne, limite2;
	int i, j, wt, i2;
	while (cpt < limite) {
		fq = (uint64_t*) calloc(int_par_ligne, sizeof(uint64_t));
		i = __builtin_ctzl(cpt);
		j = 0;
		while (j < int_par_ligne) {
			q[j] ^= base[i*int_par_ligne + j];
			fq[j] = q[j] ^ mot[j]; // on stock le résultat de mot + q
			j += 1;
		}
		// énumère la fonction lineaire
		l = (uint64_t*) calloc(int_par_ligne, sizeof(uint64_t));
		limite2 = (uint64_t)1 << code_lin.dim;
		cpt2 = 1;
		fql = (uint64_t*) calloc(int_par_ligne, sizeof(uint64_t));
		while (cpt2 < limite2) {
			i2 = __builtin_ctzl(cpt2);
			j = 0;
			wt = 0;
			while (j < int_par_ligne) {
				l[j] ^= base_lin[i2*int_par_ligne + j];
				fql[j] = fq[j] ^ l[j]; // stock mot + q + l et on regarde son poid
				wt += __builtin_popcountl(fql[j]);
				j += 1;
			}
			//on regarde si le poid correspon à ce que l'on cherche
			if (check_poid_spec(wt) == 1) res += 1;
			cpt2 += 1;
		}
		free(fql);
		cpt += 1;
	}
	free(base_lin);
	free(fq);
	free_code(code_lin);
	return res;
}


int main(int argc, char *argv[]) {
	int ffdimen, ffsize, opt, job=0, module=1, val;
	FILE *src;

	while ((opt = getopt(argc, argv, "k:n:f:j:m:t:")) != -1) {
		switch(opt) {
			case 'n':
				ffdimen = atoi(optarg);
				ffsize = 1 << ffdimen;
				break;
			case 'f':
				src = fopen(optarg, "r");
				break;
			case 'j':
				job = atoi(optarg);
				break;
			case 'm':
				module = atoi(optarg);
				break;
		}
	}

	unsigned char *boole;
	uint64_t *mot;
	code c = RMH(2, ffdimen);
	uint64_t *base;
	base = code_to_int(c);
	int cpt = 0, int_par_ligne = (c.longueur+63)/64, nh = 0;
	while ((boole = load_boole(src, &val, ffsize))){
		if (cpt % module == job) {
			mot = boole_to_int(boole, ffsize);
			nh += enum_spec_2_4_7(mot, base, ffdimen, c.dim, int_par_ligne);
			free(mot);
		}
		free(boole);
		cpt += 1;
	}
	fclose(src);
	free_code(c);
	printf("N(h) = %d\n", nh);
	return 0;
}
