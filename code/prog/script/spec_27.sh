#!/usr/bin/bash

SRC=${1-../data/B-3-4-7.dat}
DST=${2:-../resultat/spec_27.txt}
start=$(date +%s)
CORE=$(nproc)

for ((j = 0; j < $CORE; j+=1)) do
	../spec_27.exe -f $SRC -n7 -j$j -m$CORE > /tmp/spec_27-$j.txt &
done
wait
end=$(date +%s)

cat /tmp/spec_27-*.txt > $DST
rm -f /tmp/spec_27*.txt

echo runtime: $((end - start))
