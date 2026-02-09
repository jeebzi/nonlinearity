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


