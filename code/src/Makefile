CFLAGS ?= -O3 -march=native
OBJECTS = boole.o code.o affichage.o distance.o util.o covering.o weight.o linked_list.o non_trivial.o walsh.o

.PHONY: clean

libmylib.a: $(OBJECTS)
	ar crs $@ $(OBJECTS)

boole.o: boole.c boole.h
	gcc $(CFLAGS) -c $< -o $@

code.o: code.c code.h
	gcc $(CFLAGS) -mpopcnt -c $< -o $@

affichage.o: affichage.c affichage.h
	gcc $(CFLAGS) -c $< -o $@

distance.o: distance.c distance.h
	gcc $(CFLAGS) -mpopcnt -c $< -o $@

util.o: util.c util.h
	gcc $(CFLAGS) -c $< -o $@

covering.o: covering.c covering.h code.h

weight.o: weight.c weight.h

linked_list.o: linked_list.c linked_list.h

non_trivial.o: non_trivial.c non_trivial.h linked_list.o

walsh.o: walsh.c walsh.h

clean:
	rm $(OBJECTS) libmylib.a
