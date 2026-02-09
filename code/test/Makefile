CFLAGS = -Wall -g
LIB = -L../src/ -lmylib

all: load_test.exe

load_test.exe: load_test.c
	gcc $(CLFAGS) $< $(LIB) -o $@
