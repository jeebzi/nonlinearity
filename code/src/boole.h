#ifndef BOOLE_H
#define BOOLE_H
#include "../include/include.h"

uchar* load_boole(FILE *src, int *num, int ffsize);
uchar* str_to_boole(char *s, int ffsize);
void print_anf(unsigned char *boole, int ffdimen, int ffsize);
void anf(unsigned char *f, int q);
int weight_boole(unsigned char *boole, int ffsize);
void add_boole(unsigned char *boole1, unsigned char *boole2, int ffsize);
uint64_t* boole_to_int(unsigned char *boole, int ffsize);
unsigned char* int_to_boole(uint64_t *mot, int ffsize);
void liste_approximation(uint64_t *mot, code c, int target);

#endif
