#!/usr/bin/bash

CORE=$(nproc)
NL=89
ITER=5000
tid=0
PARM=nothing


while getopts "t:i:c:ip:" opt
do
	case $opt in
		t) NL=$OPTARG;;
		i) ITER=$OPTARG;;
		c) CORE=$OPTARG;;
		p) PARM=$OPTARG;;
		*)
			echo -f id stab -t target -i nb iter -c nb core
			exit;;
	esac
done

if [ ! -d $HOME/databent ] ; then
	bash ./download.sh
fi


#liste de tout les repértoire stab
all_stab=$(ls  -d $HOME/databent/bent/stab-*)

start=$(date +%s)
num=0

for stab in $all_stab ; do
	if [ $PARM = $num ] ; then
	#extraire tid
	tid=$(echo $stab |sed "s/stab-//")
	tid=$(basename $tid)
	./recherche_distance_stab.sh -f$tid -t$NL -i$ITER -c$CORE
	fi
	let num=1-num
done

end=$(date +%s)
echo total run time $((end - start))
