CFLAGS?=-Wall -g

.PHONY: sans.s avec.s all

all: sans.s avec.s

sans.s: main.c
	gcc -S -masm=intel $(CFLAGS) $< -o $@

avec.s: main.c
	gcc -S -masm=intel -mbmi $(CFLAGS) $< -o $@

