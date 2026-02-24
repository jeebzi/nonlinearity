#!/usr/bin/bash



dir=$HOME/databent/bent/
core=$( nproc )
running=0
tid=0

while getopts "j:t:m:r:" opt
do
        case $opt  in
                t) tid=$OPTARG;;
                r) run=$OPTARG;;
                j) jno=$OPTARG;;
                m) map=$OPTARG;;
                *)
                        echo -taskid  -rtasktorun  -jobno  -m
                        exit
                ;;
        esac
done

if [ $tid = 0 ]; then
	echo tid ?
	exit
fi

src=stab-$tid


for file in $dir/$src/bent-*.zip
do
	name=$( basename  -s zip $file )out

	echo $name

	if [  -f  $name  ]  ; then
		 ./unzip.exe $file    > /tmp/$name  &
	fi
   (( running++ ))
    if (( running >= core )); then
        wait -n
    ((running--))
    fi


done

wait

grep  anf   /tmp/bent-*.out   > /tmp/all-$tid.txt

