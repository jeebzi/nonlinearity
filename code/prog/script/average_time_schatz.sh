#!/usr/bin/bash


while getopts "f:n:i:" opt
do
	case $opt in
		f) SRC=$OPTARG;;
		i) iter=$OPTARG;;
		n) nb_sample=$OPTARG;;
	esac
done

sum=0
i=1
while [ $i -le $iter ]; do

	one=0
	shuf -n $nb_sample $SRC > /tmp/shuf.txt
	start=$(date +%s)
	../exp_schatz.exe -n7 -k2 -t88 -f /tmp/shuf.txt
	end=$(date +%s)
	one=$(echo "scale=4; ($end - $start)/$nb_sample" |bc)
	sum=$(echo $one + $sum|bc)
	echo "temp pour une fonction $one"
	i=$(expr $i + 1)

done
sum=$(echo "scale=4; $sum / $iter"|bc)
echo temps moyen final pour traiter une fonction = $sum
