#ifndef DISTANCE_H
#define DISTANCE_H

#include "../include/include.h"

int distance_mot_code_zip(uint64_t *mot, uint64_t *base, int ffsize, int nb_ligne);
int *distribution_distance(uint64_t *mot, uint64_t *base, int ffsize, int nb_ligne);
int distance_mot_code_min(uint64_t *mot, uint64_t *base, uint64_t ffsize, int nb_ligne, int target);
int distance_probabiliste(code c, uchar *boole, int ffsize, int nb_tour, int target);

#endif
