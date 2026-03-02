#ifndef CODE_H
#define CODE_H

#include "../include/include.h"

typedef struct code {
	int longueur;
	int dim;
	unsigned char *G;
	int* pivot;
}code;

typedef struct {
	int longueur;
	int dim;
	uint64_t *G;
}code64;

code init_code(int dim, int longueur);
void free_code(code c);
code RM(int k, int m);
code RMH(int k, int m);
int bstdimen(int s, int t, int m);
code B(int s, int t, int m);
int binomial(int k, int m);
int rmdimen(int k, int m);
unsigned char* extraire_ligne(code c, int num_ligne);
int calcule_distance_mot_code(code c, unsigned char *boole, int ffsize);
uint64_t* code_to_int(code c);
void pivotage(uint64_t *words, uint64_t *mot, int ffsize, int nb_ligne, int int_par_ligne);
code64 code_to_code64(code c);

#endif
