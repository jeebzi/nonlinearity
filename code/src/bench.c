int distance_mot_code_bench(uint64_t *mot, uint64_t *base, uint64_t ffsize, int nb_ligne, int target, int *iter, int *rejet) {
	/*
	 * calcule la distance entre un mot et un code, renvoie la valeur de la distance si elle st supérieure ou égale
	 * à la target -1 sinon
	 */
	int *iter = 0, *rejet = -1;
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
		if (wt < target){ *rejet = wt; return -1};
		if (wt < score) score = wt;
		cpt += 1;
	}
	return score;
}
