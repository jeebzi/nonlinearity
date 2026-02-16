CFLAGS = -Wall -g
LIB = -L../src -lmylib

.PHONY: clean

all: calc_nl.exe distribution.exe approximation.exe recherche_distance.exe

calc_nl.exe: calc_nl.c
	gcc $(CFLAGS) $< $(LIB) -o $@

distribution.exe: distribution.c
	gcc $(CFLAGS) $< $(LIB) -o $@

approximation.exe: approximation.c
	gcc $(CFLAGS) $< $(LIB) -o $@

recherche_distance.exe: recherche_distance.c
	gcc $(CFLAGS) $< $(LIB) -o $@

clean:
	rm *.exe
