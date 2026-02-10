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

#endif
