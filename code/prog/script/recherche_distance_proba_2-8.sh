#!usr/bin/bash

NL=${2:-88}
ITER=${3:-1000}
SRC=${1}
start=$(date +%s)

for j in {0..13}; do
	../recherche_distance_proba.exe -f $SRC -k2 -n8 -t$NL -i$ITER -m14 -j$j > /tmp/filtre_2-8-$NL-$ITER-$j.txt &
done
wait

end=$(date +%s)

cat /tmp/filtre_2-8-$NL-$ITER*.txt > ../resultat/filtre_2-8/filtre_2-8-$NL-$ITER.txt

echo runtime: $((end - start))
wc -l ../resultat/filtre_2-8/filtre_2-8-$NL-$ITER.txt

