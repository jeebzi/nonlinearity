#!/usr/bin/bash

if test ! -d $HOME/databent ; then
	wget -r -nH -P $HOME https://langevin.univ-tln.fr/data/bent/
	mv $HOME/data $HOME/databent
	cd $HOME/databent/
	ls $HOME/databent/bent/*/*html* | xargs rm
	rm $HOME/databent/bent/*html*
	echo "saved in $HOME/databent"
else
	echo file exist
fi

