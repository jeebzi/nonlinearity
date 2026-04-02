#ifndef WALSH_H
#define WALSH_H
#include "../include/include.h"
#include "affichage.h"
#include "code.h"

void fourier_transform(int *boole, int ffsize);
int* representation_signe(uchar *boole, int ffsize);
int sup_walsh(uint64_t *f, int ffdimen, int ffsize);

#endif
