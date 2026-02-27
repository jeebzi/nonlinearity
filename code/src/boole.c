#include "boole.h"
#include "util.h"

uchar* str_to_boole(char *s, int ffsize) {
	/*
	 * transforme une chaine de charactère en fonvtion boléeenne représenter par tableau de uchar
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
		if (*s == '1') s+= 1;
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

void anf(unsigned char *f, int q) {
	/*
	 * tranforme un tableau de uchar représentant la table de vérité de la fontion en représentation anf et vice versa
	 * in place
	 */
	if(q==1) return;
	anf(f, q/2);
	anf(&f[q/2], q/2);
	for(int x=0; x<q/2; x++){
		f[x+q/2] ^= f[x];
	}
}

void print_anf(unsigned char *boole, int ffdimen, int ffsize) {
	/*
	 * prend une fonction booléenne uchar* et affiche sa représentation anf sur la sortie standard
	 */
	int flag = 0;
	anf(boole,ffsize);
	printf("anf=");
	for(int u=0; u<ffsize; u++){
		if(boole[u] ){
			if(flag==0){flag=1;}
			else{
				printf("+");
			}
			if (u==0) printf("1");
			else
			for(int i=0; i<ffdimen; i++){
				if(u&(1<<i)){
					printf("%c",'a'+i);
				}
			}
		}

	}
	printf("\n");
	anf(boole,ffsize);
}

int weight_boole(unsigned char *boole, int ffsize) {
	/*
	 * retourne le poid binaire d'une fonction booléenne représenté par un tableau
	 */
	int res = 0, i = 0;
	while (i < ffsize) {
		res += boole[i];
		i += 1;
	}
	return res;
}

void add_boole(unsigned char *boole1, unsigned char *boole2, int ffsize) {
	/* in place, calcule l'addition dans F2 de deux fonctions booléeenne représenté part tab de uchar
	 */
	int i = 0;
	while (i < ffsize) {
		boole1[i] ^= boole2[i];
		i += 1;
	}
}

uint64_t* boole_to_int(unsigned char *boole, int ffsize) {
	/*
	 * tranforme une fonction boléenne (TT) représenté par un tableau de uchar par un pointeur sur uint64
	 * avec le premier indice du tableau représenté par le bit de poid faible du premier entier pointé
	 */
	uint64_t *res;
	int int_par_ligne = (ffsize + 63) / 64;
	res = (uint64_t*) calloc(int_par_ligne, sizeof(uint64_t));
	int i = 0;
	while (i < ffsize) {
		if (boole[i] == 1)
			res[i/64] |= (uint64_t)1 << (i%64);
		i += 1;
	}
	return res;
}


unsigned char* int_to_boole(uint64_t *mot, int ffsize) {
	/*
	 * prend une fonction booléenne représenter par n uint64 et renvoie ça version représenté par un tableau de uchar
	 */
	unsigned char *res;
	res = (unsigned char*) calloc((size_t)ffsize, sizeof(unsigned char));
	int i = 0;
	while (i < ffsize) {
		res[i] = (mot[i/64] >> i%64) & 1;
		i += 1;
	}
	return res;
}

uint64_t* add_boole_int(uint64_t *b1, uint64_t *b2, int n) {
	/*
	 * prend de fonction représenté par des tableaux de uint de longueur n
	 * et renvoie leur somme
	 */
	uint64_t *res;
	res = (uint64_t*) calloc(n, sizeof(uint64_t));
	int i = 0;
	while (i < n) {
		res[i] = b1[i] ^ b2[i];
		i += 1;
	}
	return res;
}

void liste_approximation(uint64_t *mot, code c, int target) {
	/*
	 * affiche les tous les mots du code à distance égale du mot
	 */
	int int_par_ligne = (c.longueur+63)/64, i, j, wt;
	uint64_t limite = (uint64_t)1 << c.dim, *words, cpt = 1, *tmp;
	words = code_to_int(c);
	uint64_t *mot_code;
	mot_code = (uint64_t*) calloc(int_par_ligne, sizeof(uint64_t));
	unsigned char *boole;

	while (cpt < limite) {
		i = __builtin_ctzl(cpt);
		//génère le mot du code
		j = 0;
		while (j < int_par_ligne) {
			mot_code[j] ^= words[i*int_par_ligne + j];
			j += 1;
		}
		tmp = copy_uint64(mot_code, int_par_ligne);
		//add
		j = 0;
		wt = 0;
		while (j < int_par_ligne) {
			tmp[j] ^= mot[j];
			wt += __builtin_popcountl(tmp[j]);
			j += 1;
		}
		if  (wt == target) {
			boole = int_to_boole(mot_code, c.longueur);
			print_anf(boole, c.dim, c.longueur);
			free(boole);
		}
		free(tmp);
		cpt += 1;
	}
	free(words);
	free(mot_code);
}

uint64_t** split(uint64_t *mot, int ffsize, int int_par_ligne) {
	/*
	 * renvoi un pointeur sur la partie gauche et droite du mot
	 */

	int mid = ffsize / 2;
	int i = 0;
	uint64_t *L, *R, **res;
	int last_left; // id du dernier entier contenant la partie gauche du mot
	last_left = mid / 64;
	res = (uint64_t**) malloc(2 * sizeof(uint64_t*));
	L = (uint64_t*) calloc(last_left + 1, sizeof(uint64_t));
	R = (uint64_t*) calloc(last_left + 1, sizeof(uint64_t));
	// si le mot est contenu dans plus qu'un entier alors on peut juste mettre la première moité dans L et l autre dans R
	if (int_par_ligne > 1) {
		int fin = int_par_ligne / 2; //int par ligne toujours divisible par 2 si > 1
		while (i < fin) {
			L[i] = mot[i];
			R[i] = mot[fin + i];
			i += 1;
		}
	}

	else {
		//sinon on doit faire bit par bit
		while (i < mid) {
			L[0] ^= ((mot[0] >> i) & 1) << i;
			R[0] ^= ((mot[0] >> i+mid) & 1) << i+mid;
			i += 1;
		}
	}
	res[0] = L;
	res[1] = R;
	return res;
}
