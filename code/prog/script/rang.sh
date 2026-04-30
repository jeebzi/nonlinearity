#!/usr/bin/bash
k=-1

while getopts "f:d:k:n:" opt
do
	case $opt in
		f) SRC=$OPTARG;;
		d) DST=$OPTARG;;
		k) k=$OPTARG;;
		n) n=$OPTARG;;
	esac
done

../filtre_homogene.exe -f $SRC -k$k -n$n > /tmp/homogene.txt

../distribution_rang.exe -f /tmp/homogene.txt -n$n > $DST

rm -f /tmp/homogene.txt

