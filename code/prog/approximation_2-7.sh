#!usr/bin/bash

for j in {0..3} ; do
	./approximation.exe -k2 -n7 -t40 -f data/NL-2-7-40.dat -j$j -m4 > ./resultat/app27_h$j.txt
done

wait
