#!/usr/bin/bash

CORE=$(nproc)
while getopts "d:k:n:i:" opt
do
	case $opt in
		d) DST=$OPTARG;;
		k) k=$OPTARG;;
		n) n=$OPTARG;;
		i) iter=$OPTARG;;
	esac
done

for ((j = 0; j<$CORE; j += 1)) do
	../bench.exe -k$k -n$n -i$iter -j$j > /tmp/bench-$j.txt &
done
wait

cat /tmp/bench-*.txt > $DST

rm -f /tmp/bench-*.txt

