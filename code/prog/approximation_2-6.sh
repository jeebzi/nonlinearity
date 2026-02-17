#!usr/bin/bash

for j in {0..2} ; do
	./approximation.exe -k2 -n6 -t18 -f data/NL-2-6-18.txt -j$j -m3 > ./resultat/app26_h$j.txt &
done

wait
