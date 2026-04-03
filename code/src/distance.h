#ifndef DISTANCE_H
#define DISTANCE_H

#include "code.h"
#include "weight.h"
#include "walsh.h"
#include "affichage.h"
#include "../include/include.h"

int distance_mot_code_zip(uint64_t *mot, uint64_t *base, int ffsize, int nb_ligne);
int *distribution_distance(uint64_t *mot, uint64_t *base, int ffsize, int nb_ligne);
int distance_mot_code_min(uint64_t *mot, uint64_t *base, uint64_t ffsize, int nb_ligne, int target);
int distance_probabiliste(code c, uchar *boole, int ffsize, int nb_tour, int target);
int distance_decode(uint64_t *mot, code64 c, code64 c2, int target, int ffdimen, int degree);
int bdistance(uint64_t **zip, code64 c, int target, int int_par_ligne);
unsigned int ftl(uint64_t *boole, int ffdimen, int ffsize, int target);

#endif
