#ifndef COVERING_H
#define COVERING_H
#include "../include/include.h"
#include "code.h"
#include "affichage.h"

uint64_t *get_covering(uint64_t *mot, code64 c, int poid_min);
int is_orphan(uint64_t *mot, code64 c, int poid_min);

#endif

