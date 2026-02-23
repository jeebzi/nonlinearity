#include "distance.h"
#include "util.h"
#include "boole.h"

int distance_mot_code_zip(uint64_t *mot, uint64_t *base, int ffsize, int nb_ligne) {
	/*
	 * calcule la distance d'un mot à un code (base) de manière plus efficace avec la représentation par entier
	 * je pense que le mot est modifié par cette fonction
	 */
	int int_par_ligne = (ffsize+63) / 64;
	int score = ffsize;
	uint64_t limite = (uint64_t)1 << nb_ligne;
	uint64_t cpt = 1;
	int i; // indice bit qui change
	int j, wt;
	while (cpt < limite) {
		i = __builtin_ctzl(cpt);
		//addition entre mot dans F2
		j = 0;
		wt = 0;
		while (j < int_par_ligne) {
			mot[j] ^= base[i*int_par_ligne + j];
			wt += __builtin_popcountl(mot[j]);
			j += 1;
		}
		if (wt < score) score = wt;
		cpt += 1;
	}
	return score;
}

int distance_mot_code_min(uint64_t *mot, uint64_t *base, uint64_t ffsize, int nb_ligne, int target) {
	/*
	 * calcule la distance entre un mot et un code, renvoie la valeur de la distance si elle st supérieure ou égale
	 * à la target -1 sinon
	 */
	int int_par_ligne = (ffsize+63) / 64;
	int score = ffsize;
	uint64_t limite = (uint64_t)1 << nb_ligne;
	uint64_t cpt = 1;
	int i; // indice bit qui change
	int j, wt;
	while (cpt < limite) {
		i = __builtin_ctzl(cpt);
		//addition entre mot dans F2
		j = 0;
		wt = 0;
		while (j < int_par_ligne) {
			mot[j] ^= base[i*int_par_ligne + j];
			wt += __builtin_popcountl(mot[j]);
			j += 1;
		}
		if (wt < target) return -1;
		if (wt < score) score = wt;
		cpt += 1;
	}
	return score;
}


int *distribution_distance(uint64_t *mot, uint64_t *base, int ffsize, int nb_ligne) {
	/*
	 * calcule la distance entre unt mot et tous les mots du code généré par la base et renvoi la distribution
	 * dans un tableau d'entier
	 */
	int *res, int_par_ligne = (ffsize+63)/64, i, j, wt;
	uint64_t cpt = 1, limite = (uint64_t)1 << nb_ligne;
	res = (int*) calloc(ffsize, sizeof(int));

	//calcule des poids des mots du coset comme dans la fonction du haut
	while (cpt < limite) {
		i = __builtin_ctzl(cpt);
		//addition entre mot dans F2
		j = 0;
		wt = 0;
		while (j < int_par_ligne) {
			mot[j] ^= base[i*int_par_ligne + j];
			wt += __builtin_popcountl(mot[j]);
			j += 1;
		}
		res[wt] += 1;
		cpt += 1;
	}
	return res;
}

int distance_probabiliste(code c, uchar *boole, int ffsize, int nb_tour, int target) {
	/*
	 * estime de manière probabiliste en utilisant la technique du pivot de Gauss la distance entre une
	 * fonction et un code, renvoie une distance min au code possible si elle est supérieur ou égale à
	 * la target -1 sinon
	 */
	uint64_t *mot, *words, *mot_cpy, *words_cpy;
	int int_par_ligne = (c.longueur+63)/64, nb_int_mat = c.dim*int_par_ligne, j;
	mot = boole_to_int(boole, ffsize);
	words = code_to_int(c);

	int cpt = 0, score = ffsize, wt;
	while (cpt < nb_tour) {
		mot_cpy = copy_uint64(mot, int_par_ligne);
		words_cpy = copy_uint64(words, nb_int_mat);

		pivotage(words_cpy, mot_cpy, ffsize, c.dim, int_par_ligne);
		//calcul poid du mot obtenu
		j = 0;
		wt = 0;
		while (j < int_par_ligne) {
			wt += __builtin_popcountl(mot_cpy[j]);
			j += 1;
		}
		if (wt < target) {
			free(mot_cpy);
			free(words_cpy);
			free(mot);
			free(words);
		       	return -1;
		}
		if (wt < score) score = wt;
		cpt += 1;
		free(mot_cpy);
		free(words_cpy);
	}
	free(mot);
	free(words);
	return score;
}
