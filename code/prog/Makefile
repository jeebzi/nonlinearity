CFLAGS ?= -O3 -march=native
LIB = -L../src -lmylib -I../src
VPATH = ../src

.PHONY: clean all

all: calc_nl.exe distribution.exe approximation.exe recherche_distance.exe recherche_distance_proba.exe spec_27.exe fdt.exe orphan.exe rang.exe filtre_homogene.exe distribution_rang.exe bench.exe non_trivial.exe tableau_poid.exe

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

fdt.exe: fdt.c -lmylib
	gcc $(CFLAGS) $< $(LIB) -o $@

orphan.exe: orphan.c -lmylib
	gcc $(CFLAGS) $< $(LIB) -o $@

rang.exe: rang.c -lmylib
	gcc $(CFLAGS) $< $(LIB) -o $@

filtre_homogene.exe: filtre_homogene.c -lmylib
	gcc $(CFLAGS) $< $(LIB) -o $@

distribution_rang.exe: distribution_rang.c -lmylib
	gcc $(CFLAGS) $< $(LIB) -o $@

bench.exe: bench.c -lmylib
	gcc $(CFLAGS) $< $(LIB) -o $@

non_trivial.exe: non_trivial.c -lmylib
	gcc $(CFLAGS) $< $(LIB) -o $@

tableau_poid.exe: tableau_poid.c -lmylib
	gcc $(CFLAGS) $< $(LIB) -o $@

clean:
	rm *.exe
