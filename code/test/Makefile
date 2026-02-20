CFLAGS ?= -Wall -g
LIB = -L../src/ -lmylib

.PHONY: clean

all: load_test.exe code_test.exe distance_test.exe boole_to_int_test.exe code_zip_test.exe int_distance_test.exe distribution_test.exe approximation_test.exe pivot_test.exe

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

clean:
	rm *.exe
