#ifndef NON_TRIVIAL_H
#define NON_TRIVIAL_H
#include "../include/include.h"
#include "linked_list.h"

link_list_uint* cherche_non_triviaux(int ffdimen, int ffsize);
int check_non_trivial(unsigned int x, unsigned int y, unsigned z, unsigned int t, int ffdimen);
int condition_non_trivial(unsigned int x, unsigned int y, unsigned int z, unsigned int t, int i, int j);

#endif
