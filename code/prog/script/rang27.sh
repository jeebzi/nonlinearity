for f in ../resultat/app27_h*; do
	base=$(basename $f)
	./rang.sh -f $f -k2 -n7 -d ../resultat/rang_$base 
done
