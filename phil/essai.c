#include <stdio.h>
#include <stdlib.h>

int *Y;
int * A, *B;

#define DIMEN 21
#define SIZE  ( 1 << DIMEN  )

int score = 0i, count = 0;

void Fourier(int *f, unsigned int n )
// Transformation de Fourier sur place.
{   
int x,y,z;
if (n>1) {
         Fourier(f,n>>1);
         Fourier(&(f[n>>1]),n>>1);
         for(x=0,y=(n>>1);  x< (n>>1); x++,y++)
                {
                z = f[x];
                f[x] = z + f[y];
                f[y] = z - f[y];
                }
         };
}   
   
void search(  int k  )
{

if ( k > score ) {
	score = k;
	printf("\nscore=%d\n", score );
}
if ( score == DIMEN ) {
	count++;
	printf("\ncount=%d\n", count );
	return;
}

int e = 1 << k;
int size = 1 << k;
for( int f = 1; f < SIZE;  f++ )
	if ( A[ e ] == B[ f ] ) {
		int q;
		for ( q = 0;  q < size &&  ( A[q ^ e] == B[ Y[q]  ^ f ] ) ; q++ );				
		if ( q == size ) {
			for(  q = 0;  q < size;  q++) 
				Y[q ^ e] = Y[ q ]  ^ f ;
			search( k + 1 );		
		 }	
	}
}	

int main( int argc, char *argv[] )
{
	A = calloc( SIZE, sizeof(int ));
	B = calloc( SIZE, sizeof(int ));
	Y = calloc( SIZE, sizeof(int ));

int n = atoi( argv[1] );

for( int i = 0; i < SIZE; i++) A[i] = random() % n;
for( int i = 0; i < SIZE; i++) B[i] = random() % n;

Fourier( A, SIZE );
Fourier( B, SIZE );

A = B;

search( 0 );


return 0;
}
