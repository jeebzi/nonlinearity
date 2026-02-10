#ifndef CODE_H
#define CODE_H

#include "../include/include.h"

typedef struct {
	int longueur;
	int dim;
	unsigned char *G;
	int* pivot;
}code;
code init_code(int dim, int longueur);
void free_code(code c);
code RM(int k, int m);
int binomial(int k, int m);
int rmdimen(int k, int m);
unsigned char* extraire_ligne(code c, int num_ligne);
int calcule_distance_mot_code(code c, unsigned char *boole, int ffsize);
uint64_t* code_to_int(code c);

#endif
