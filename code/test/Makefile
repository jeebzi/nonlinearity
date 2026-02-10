CFLAGS = -Wall -g
LIB = -L../src/ -lmylib

all: load_test.exe code_test.exe distance_test.exe boole_to_int_test.exe

load_test.exe: load_test.c
	gcc $(CLFAGS) $< $(LIB) -o $@

code_test.exe: code_test.c
	gcc $(CLFAGS) $< $(LIB) -o $@

distance_test.exe: distance_test.c
	gcc $(CFLAGS) $< $(LIB) -o $@

boole_to_int_test.exe: boole_to_int_test.c
	gcc $(CFLAGS) $< $(LIB) -o $@
