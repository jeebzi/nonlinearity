#include <all.h>
#include "../include/include.h"

/* le but de ce programme est de construire le tableau L tel que L[q] = max wt(h+q+l) avec h nos
 * fonctions HNL pour RM(2,7) q les quadratique homogènes et l les fonctions affines
 */


int  maxdepth, goal = 96, size;
int *L, *R, *img;
int EXIT;


void search( int k )
{
if ( EXIT ) return ;
if ( k == 21 ) {
	EXIT = 1;
	return;
}
if ( k > maxdepth ) {
	printf("\ndepth=%d", k );
	maxdepth = k;
}
int e = 1 << k;
for( int y = 0; y < size; y++ )  
	if (  R[ y ] + L[ e ] >= goal  ) {
		int x;
	       for ( x = 0; x < e  &&   L[ x ^ e  ] + R[ img[ x ]  ^ y ] >=  goal ; x++  ) ;;
               if ( x == e ) {
	       		for ( x = 0; x < e ; x++  )
				img[ x ^ e ]  = img[ x ] ^ y;
		search( k + 1 );
	       }	       
	}
}
int base[ 64 ];
int rank ( int b[ 64], int r )
{ int bs[ 64 ];
  for( int i = 0; i < r; i++ )
	  bs[i] = b[i];
  for( int i = 0 ; i < r; i++) {
	  int p = __builtin_ctz( bs[i]  );
	  for( int j = i+1; j < r; j++ )
		  if ( (1<<p) & bs[j] ) 
			  bs[j]^= bs[i];
  }
  return   bs[r-1] > 0; 
}

int bonnebase( int t[] )
{
int r = 0, i = 0, c = 0;
while ( i < size  ) {
	if ( t[i] <= 44  ) {
		base[ r ] = i;
		if (  rank( base, r+1 )  ) r++;
		c++;
		//printf("\nc=%d r=%d", c, r );
	}
	i++;
}	
printf("\nrank=%d\n", r );
}	

void doit( int *src, int *dst )
{
	img = calloc( size, sizeof *img  );
	L = src;
	R = dst;
	maxdepth = 0;
	EXIT = 0;
	search(  0  );
	free( img );
	puts("fait");
}

int *tableau_poid(uint64_t *h, int ffdimen, int ffsize) {
	int int_par_ligne = (ffsize+63)/64;
	int *tab; /* tableau des poid */
	int id_tab = 0;

	code base_tmp = RMH(2, ffdimen);
	code64 base_quad = code_to_code64(base_tmp);
	free_code(base_tmp);
	unsigned int longueur_tab = 1 << base_quad.dim;
	tab = (int*) calloc(longueur_tab, sizeof(int));
	base_tmp = RM(1, ffdimen);
	code64 base_affine = code_to_code64(base_tmp);
	free_code(base_tmp);
	unsigned int limite = 1 << base_affine.dim;

	uint64_t *q, *l;
	q = (uint64_t*) calloc(int_par_ligne, sizeof(uint64_t));
	l = (uint64_t*) calloc(int_par_ligne, sizeof(uint64_t));
	unsigned int cpt = 1, cpt2;
	int j, wt, i;
	/* énum q */
	// tu oublies q = 0 ?
	//
	while (cpt < longueur_tab) {
		i = __builtin_ctz(cpt);
		id_tab ^= 1 << i;
		j = 0;
		while (j < int_par_ligne) {
			q[j] ^= base_quad.G[i*int_par_ligne + j];
			j += 1;
		}
		cpt2 = 1;
		memset(l, 0, int_par_ligne);
		/* énum l */
		// Attention de ne pas oublier : l = 0 !
		int min = 0;
		for( j = 0; j < int_par_ligne; j++ )
			min += __builtin_popcountl(h[j] ^ q[j]);
		while (cpt2 < limite) {
			i = __builtin_ctz(cpt2);
			j = 0;
			wt = 0;
			while (j < int_par_ligne) {
				l[j] ^= base_affine.G[i*int_par_ligne + j];
				wt += __builtin_popcountl(h[j] ^ q[j] ^ l[j]);
				j += 1;
			}
			if ( wt <  min ) min = wt;
			cpt2 += 1;
		}
		tab[id_tab] = min;
		cpt += 1;
	}
	free_code64(base_quad);
	free_code64(base_affine);
	free(q);
	free(l);
	return tab;
}

void pdistrib( int t[], int n )
{ int mult[ 129] ={0};
   for( int i = 0; i < n; i++ )
	mult[ t[ i ] ]++;
   printf("\n");
   for( int j = 0; j <= 128; j++ )
	   if ( mult[ j ] ) printf(" %d [%d]", mult[j], j );
	printf("\n");
}
int main(int argc, char *argv[]) {
	int ffdimen, ffsize, num, opt, job=0, module=1, val, rang_val;
	FILE *src;

	while ((opt = getopt(argc, argv, "n:f:g:")) != -1) {
		switch(opt) {
			case 'n':
				ffdimen = atoi(optarg);
				ffsize = 1 << ffdimen;
				break;
			case 'f':
				src = fopen(optarg, "r");
				break;
			case 'g':
				goal = atoi(optarg) ;
				break;
		}
	}

	uchar *f;
	uint64_t *h;
	int * tab[ 4 ];
	int i = 0;
	size = 1 << ( ffdimen * ( ffdimen -1 )/2 );
	while ((f = load_boole(src, &num, ffsize))) {
		h = boole_to_int(f, ffsize);
		tab[i]  = tableau_poid(h, ffdimen, ffsize);
		pdistrib( tab[i] , size );
		bonnebase( tab[i] );
		i++;
		printf("done\n");
	}
	free(h);
	assert( i == 4 );
	return 0;

	for( i = 0; i < 4; i++ )
	for( int j = i+1; j < 4; j++ )
		doit(  tab[i],  tab[j]  );
	return 0;
}
