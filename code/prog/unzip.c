#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int ffsize=256;
int ffdimen=8;

typedef uint64_t zip[4];
typedef char* boole;

#define one ( ( u_int64_t ) 1 )

#define WT(f) (__builtin_popcountll(f[0])+__builtin_popcountll(f[1])+__builtin_popcountll(f[2])+__builtin_popcountll(f[3]))




int loadzip( zip  z, FILE * source )
{ 
	int nb = fread( & (z[0]),  sizeof(int64_t) , 4, source );
	return ( nb == 4 );
}

char * getboole(  void )
{
	return calloc( ffsize, 1 );
}


boole getBoolezip( zip w )
{ boole f = getboole();
  int i;
  for (i = 0; i < 64; i++) {
	f[i]     = ( w[0] & ( one << i ) ) > 0 ;
	f[i+64]  = ( w[1] & ( one << i ) ) > 0 ;
	f[i+128] = ( w[2] & ( one << i ) ) > 0 ;
	f[i+192] = ( w[3] & ( one << i ) ) > 0 ;
    }
  return f;
}


void pTT( FILE*dst, boole f)

{
int x;

fprintf(dst, "\nTT=");

for( x = 0; x < ffsize ; x++)
        fprintf(dst, " %d", f[x]);


}
void xform( boole f, int n)
{
int x , y;
if ( n > 1 ) {
         xform(f,n>>1);
         xform(&(f[n>>1]), n>>1);
         for(x=0, y=(n>>1);  x< (n>>1); x++, y++)
                 f[y] = f[x]^f[y];
         }
}



void panf( FILE*dst, boole f)
{
int x,y,i,p;
char aux[ ffsize ];
for( x = 0; x < ffsize; x++ )
	aux[x] = f[x];

fprintf(dst, "\n\nanf=");
p = 1;
xform( aux, ffsize);
if ( aux[0] )
        fprintf( dst, "1+" );
for( x = 1; x < ffsize ; x++)
   if ( aux[x] == 1 ) {
        i=0;
        y=x;
        if (p==0) fprintf(dst, "+"); else p=0;
        while (y>0)
              {
              if ( y & 1 ) fprintf(dst, "%c", i + 'a');
              i++;
              y=y>>1;
              }
        }
}

void pxxx( FILE*dst, boole f)
{
int x,y,i,p;
char aux[ ffsize ];
for( x = 0; x < ffsize; x++ )
	aux[x] = f[x];

fprintf(dst, "\n\n");
p = 1;
xform( aux, ffsize);
if ( aux[0] )
        fprintf( dst, "1+" );
for( x = 1; x < ffsize ; x++)
   if ( aux[x] == 1 ) {
        i=0;
        y=x;
        if (p==0) fprintf(dst, "+"); else p=0;
        while (y>0)
              {
              if ( y & 1 ) fprintf(dst, "x_%d", i+1);
              i++;
              y=y>>1;
              }
        }
}


int limite   = 0;
int output   = 'a';
int randout  = 1;

void usage ( char *s  )
{
	fprintf(stderr, "Usage: %s atx l: r:\n", s);
puts("option:\n-a alphabetic variables\n-x anf standard\n-t true table\n-l number of output\n-r randomize");
puts("example:\nunzip.exe -a  -r123 -l5 filename\n\twill outputs 5 bent functions using alphabetic format\n\tusing the tossing probability is 1/123...");
}
void option(int argc, char *argv[])
{

    int opt;
    while ((opt = getopt(argc, argv, "atxl:r:h")) != -1) {
        switch (opt) {
        case 'a':
            output = 'a';
            break;
        case 'x':
            output = 'x';
            break;
        case 't':
            output = 't';
            break;
        case 'l':
            limite = atoi(optarg);
            break;
        case 'r':
            randout = atoi(optarg);
            break;
	case 'h' :
        default:                
	    usage( argv[0]);
            exit(EXIT_FAILURE);
        }
    }
}

int main(int argc, char *argv[])
{


    zip z;
    int num = 0;
    option( argc, argv );

    srandom( time(NULL) );

    FILE *src = fopen( argv[optind], "r" );

    if ( ! src  ) {
	    perror("bad file");
	    return(1);
    }

    while (  loadzip( z, src ) ) {
	        boole f = getBoolezip(z);
		if ( 0  == random() % randout  ){
	        	switch( output ) {
			case 't' : pTT(stdout, f ); break ;
			case 'a' : panf(stdout, f ); break ;
			case 'x' : pxxx(stdout, f ); break ;
		}
		num++;
		}
		free(f);
		if ( limite && limite <= num  ) break;
    	}

    fclose(src);	
    printf("\n#%d bent found...\n", num);
    return 0;
}
