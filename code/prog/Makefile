CFLAGS ?= -O3 -march=native
LIB = -L../src -lmylib -I../src
VPATH = ../src

.PHONY: clean all

all: calc_nl.exe distribution.exe approximation.exe recherche_distance.exe recherche_distance_proba.exe spec_27.exe

calc_nl.exe: calc_nl.c -lmylib
	gcc $(CFLAGS) $< $(LIB) -o $@

distribution.exe: distribution.c -lmylib
	gcc $(CFLAGS) $< $(LIB) -o $@

approximation.exe: approximation.c -lmylib
	gcc $(CFLAGS) $< $(LIB) -o $@

recherche_distance.exe: recherche_distance.c -lmylib
	gcc $(CFLAGS) $< $(LIB) -o $@

recherche_distance_proba.exe: recherche_distance_proba.c -lmylib
	gcc $(CFLAGS) $< $(LIB) -o $@

spec_27.exe: spec_27.c -lmylib
	gcc $(CFLAGS) $< $(LIB) -o $@

clean:
	rm *.exe
