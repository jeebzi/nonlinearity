#ifndef BENCH_H
#define BENCH_H
#include "../include/include.h"
#include "weight.h"
#include "code.h"
#include "boole.h"
#include "walsh.h"

int distance_mot_code_bench(uint64_t *mot, uint64_t *base, uint64_t ffsize, int nb_ligne, int target, unsigned int *iter, int *rejet);
unsigned int ftl_bench(uint64_t *f, int ffdimen, int ffsize, int target, unsigned int *iter, int *rejet);

#endif

