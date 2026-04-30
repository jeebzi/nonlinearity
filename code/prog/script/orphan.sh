#!/usr/bin/bash
CORE=$(nproc)
SRC=../../../phil/stab-35672555520-NL_2-8-92-5000.txt
DST=../resultat/orphan_$(basename $SRC).txt

while getopts "f:d:k:n:" opt
do
	case $opt in
		f) SRC=$OPTARG;;
		d) DST=$OPTARG;;
		k) k=$OPTARG;;
		n) n=$OPTARG;;
	esac
done

for ((j = 0; j < $CORE; j+=1)) do
	../orphan.exe -f $SRC -k$k -n$n -m$CORE -j$j > /tmp/orphan-$j.txt &
done
wait

cat /tmp/orphan-*.txt > $DST
rm -f /tmp/orphan*

