CFLAGS = -g -Wall
OBJECTS = boole.o code.o affichage.o

.PHONY: clean

libmylib.a: $(OBJECTS)
	ar crs $@ $(OBJECTS)

boole.o: boole.c boole.h
	gcc $(CFLAGS) -c $< -o $@

code.o: code.c code.h
	gcc $(CFLAGS) -mpopcnt -c $< -o $@

affichage.o: affichage.c affichage.h
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJECTS) libmylib.a
