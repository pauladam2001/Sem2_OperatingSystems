#!/bin/sh

find $1 -type f -name "*.log" | while read X;do
	touch aux.txt
	sort $X >> aux.txt  #SAU doar > SAU cat $X | sort ...
	mv aux.txt $X
	#rm aux.txt
done
