CFLAGS = -g -Wall
OBJECTS = boole.o

.PHONY: clean

libmylib.a: $(OBJECTS)
	ar crs $@ $(OBJECTS)

boole.o: boole.c boole.h
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJECTS) libmylib.a
