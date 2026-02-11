CFLAGS = -Wall -g
LIB = -L../src -lmylib

.PHONY: clean

all: calc_nl.exe distribution.exe

calc_nl.exe: calc_nl.c
	gcc $(CFLAGS) $< $(LIB) -o $@

distribution.exe: distribution.c
	gcc $(CFLAGS) $< $(LIB) -o $@

clean:
	rm *.exe
