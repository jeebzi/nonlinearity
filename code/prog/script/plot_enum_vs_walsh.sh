#!/usr/bin/bash

rm -f plot_enum.txt plot_walsh.txt

while getopts "s:" opt
do
	case $opt in
		s) sample=$OPTARG;;
	esac
done


for ((n = 8; n<=17; n += 1)) do
../bench_enum.exe -n$n -k1 -s$sample -t0 -S -r >> plot_enum.txt
../bench_walsh.exe -n$n -s$sample -r >> plot_walsh.txt
done
