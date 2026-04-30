#!/usr/bin/bash

CORE=$(nproc)
NL=88
ITER=10000
tid=0
DST=-1

while getopts "f:t:c:n:d:" opt
do
	case $opt in
		f) SRC=$OPTARG;;
		t) NL=$OPTARG;;
		c) CORE=$OPTARG;;
		n) N=$OPTARG;;
		d) DST=$OPTARG;;
		*)
			echo -f source -t target  -c nb core -n nb variable
			exit;;
	esac
done

if [[ $DST == -1 ]] ; then
	DST=../resultat/NL-$SRC
fi



start=$(date +%s)
for ((j = 0; j<$CORE; j+=1)) do
	../ftl.exe -f $SRC -n$N -t$NL -m$CORE -j$j > /tmp/ftl-$j.txt &
done
wait

end=$(date +%s)

cat /tmp/ftl-*.txt > $DST
rm -f /tmp/ftl-*.txt

echo runtime: $((end - start))
wc -l $DST
