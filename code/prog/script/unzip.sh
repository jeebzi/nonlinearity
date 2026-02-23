#!/usr/bin/bash



dir=$HOME/databent/bent/
src=$1


for file in $dir/$src/bent-*.zip
do
	name=$( basename  -s zip $file )out

	echo $name

	if [  -f  $name  ]  ; then
		 echo ./unzip.exe $file 
	fi
done

grep  anf   bent-*.out   > /tmp/$src.txt

