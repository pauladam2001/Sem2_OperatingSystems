#!/bin/sh

touch aux.txt

for F in `find $1 -type f`; do
	filetype=`file $F`
	okay=`echo $filetype | grep -E -c "\<C\>"`
	if [ $okay -ge 1 ]; then
		rm $F
	else
		echo $F >> aux.txt	
	fi
done

cat aux.txt | sort

rm aux.txt
