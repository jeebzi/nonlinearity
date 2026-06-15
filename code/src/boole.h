#ifndef BOOLE_H
#define BOOLE_H
#include "../include/include.h"
#include "code.h"

uchar* load_boole(FILE *src, int *num, int ffsize);
uchar* str_to_boole(char *s, int ffsize);
void print_anf(unsigned char *boole, int ffdimen, int ffsize);
void anf(unsigned char *f, int q);
int weight_boole(unsigned char *boole, int ffsize);
void add_boole(unsigned char *boole1, unsigned char *boole2, int ffsize);
uint64_t* boole_to_int(unsigned char *boole, int ffsize);
unsigned char* int_to_boole(uint64_t *mot, int ffsize);
void liste_approximation(uint64_t *mot, code c, int target);
uint64_t** split(uint64_t *mot, int ffsize, int int_par_ligne);
int correlation(uint64_t *f1, uint64_t *f2, int ffsize);
int rang(uint64_t *f, int ffdimen, int ffsize);
int is_homogene(unsigned char *mot, int degree, int ffsize);
uchar* random_boole(int ffdimen, int degre);
uint64_t* random_boole_int(int ffsize);
uint64_t* indice_to_boole(uint64_t indice, code64 c);
uint64_t *merge(uint64_t *h, uint64_t *g, int ffsize);

#endif
