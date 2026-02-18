#ifndef INCLUDE_H
#define INCLUDE_H

typedef unsigned char uchar;
typedef struct code {
	int longueur;
	int dim;
	unsigned char *G;
	int* pivot;
}code;

#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <assert.h>

#include "../src/boole.h"
#include "../src/code.h"
#include "../src/affichage.h"
#include "../src/distance.h"
#include "../src/util.h"

#endif
