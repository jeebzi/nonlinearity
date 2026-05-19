CFLAGS ?= -Wall -g
LIB = -L../src/ -lmylib -I../src/
VPATH=../src

.PHONY: clean

all: load_test.exe code_test.exe distance_test.exe boole_to_int_test.exe code_zip_test.exe int_distance_test.exe distribution_test.exe approximation_test.exe pivot_test.exe split_test.exe non_trivial.exe walsh.exe ftl_t.exe indice_test.exe merge_t.exe

load_test.exe: load_test.c
	gcc $(CLFAGS) $< $(LIB) -o $@

code_test.exe: code_test.c
	gcc $(CLFAGS) $< $(LIB) -o $@

code_zip_test.exe: code_zip_test.c
	gcc $(CLFAGS) $< $(LIB) -o $@

distance_test.exe: distance_test.c
	gcc $(CFLAGS) $< $(LIB) -o $@

boole_to_int_test.exe: boole_to_int_test.c
	gcc $(CFLAGS) $< $(LIB) -o $@

int_distance_test.exe: int_distance_test.c
	gcc $(CFLAGS) $< $(LIB) -o $@

distribution_test.exe: distribution_test.c
	gcc $(CFLAGS) $< $(LIB) -o $@

approximation_test.exe: approximation_test.c
	gcc $(CFLAGS) $< $(LIB) -o $@

pivot_test.exe: pivot_test.c
	gcc $(CFLAGS) $< $(LIB) -o $@

split_test.exe: split_test.c -lmylib
	gcc $(CFLAGS) $< $(LIB) -o $@

non_trivial.exe: non_trivial.c -lmylib
	gcc $(CFLAGS) $< $(LIB) -o $@

walsh.exe: walsh.c -lmylib
	gcc $(CFLAGS) $< $(LIB) -o $@

ftl_t.exe: ftl_t.c -lmylib
	gcc $(CFLAGS) $< $(LIB) -o $@

indice_test.exe: indice_test.c -lmylib
	gcc $(CFLAGS) $< $(LIB) -o $@

merge_t.exe: merge_t.c -lmylib
	gcc $(CFLAGS) $< $(LIB) -o $@

clean:
	rm *.exe
