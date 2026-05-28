#!/usr/bin/bash

CORE=$(nproc)
k=2
n=7
DST=$HOME/res_schatz.txt
while getopts "f:n:k:t:c:d:" opt
do
	case $opt in
		f) SRC=$OPTARG;;
		n) n=$OPTARG;;
		k) k=$OPTARG;;
		t) target=$OPTARG;;
		c) CORE=$OPTARG;;
		d) DST=$OPTARG;;

	esac
done

for ((j = 0; j<$CORE; j += 1)) do
	../exp_schatz.exe -k$k -n$n -f $SRC -m$CORE -j$j > /tmp/schatz-$j.txt &
done
wait

cat /tmp/schatz-*.txt > $DST

rm -f /tmp/schatz-*txt
