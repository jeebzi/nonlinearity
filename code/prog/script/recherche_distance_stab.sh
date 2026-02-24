#!/usr/bin/bash

CORE=$(nproc)
NL=88
ITER=10000
tid=0

while getopts "f:t:i:c:" opt
do
	case $opt in
		f) tid=$OPTARG;;
		t) NL=$OPTARG;;
		i) ITER=$OPTARG;;
		c) CORE=$OPTARG;;
		*)
			echo -f id stab -t target -i nb iter -c nb core
			exit;;
	esac
done

if [ ! -f /tmp/all-$tid.txt ] ; then
	echo "le fichier n'exisite pas, lancez ./unzip.sh -t $tid"
	exit
fi
SRC=/tmp/all-$tid.txt

if [ ! -d $HOME/databent/ ] ; then
	echo "pas de fichier databent lancez ./download.sh"
	exit
fi
if [ ! -d $HOME/databent/result/ ] ; then
	mkdir $HOME/databent/result
fi
mkdir -p $HOME/databent/result/stab-$tid

DST=$HOME/databent/result/stab-$tid/NL_2-8-$NL-$ITER.txt

if test -f $DST ; then
	echo le fichier de destination existe déjà êtes vous sûr de vouloir écraser ce travail ? y/n
	read choice
fi

if [[ $choice == n ]] ; then
	echo "interrupted"
	exit
fi



start=$(date +%s)

for ((j = 0; j<$CORE; j+=1)) do
	../recherche_distance_proba.exe -f $SRC -k2 -n8 -t$NL -i$ITER -m14 -j$j > /tmp/filtre_2-8-$NL-$ITER-$j.txt &
done
wait

end=$(date +%s)

cat /tmp/filtre_2-8-$NL-$ITER-*.txt > $DST
rm -f /tmp/filtre_2-8-$NL-$ITER-*.txt

echo runtime: $((end - start))
wc -l $DST
