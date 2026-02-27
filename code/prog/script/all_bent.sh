#!/usr/bin/bash

CORE=$(nproc)
NL=89
ITER=10000
tid=0

while getopts "t:i:c:" opt
do
	case $opt in
		t) NL=$OPTARG;;
		i) ITER=$OPTARG;;
		c) CORE=$OPTARG;;
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
for stab in $all_stab ; do
	#extraire tid
	tid=$(echo $stab |sed "s/stab-//")
	tid=$(basename $tid)
	bash ./recherche_distance_stab.sh -f$tid -t$NL -i$ITER -c$CORE
done

end=$(date +%s)
echo total run time $((end - start))
