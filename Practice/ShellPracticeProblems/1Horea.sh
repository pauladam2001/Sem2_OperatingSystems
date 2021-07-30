#!/bin/sh

total=0
if ! test -d $1; then
	echo Directory does not exist
else
	for F in `ls $1`; do
		if [ -f $F ]; then
			N=`ls -l $F | awk '{print $5}'`
			total=`expr $total + $N`			
		fi 
	done
echo $total
fi

#OR for F in `find $1 -type f`
