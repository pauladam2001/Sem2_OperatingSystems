#!/bin/bash

sum=0
ct=0

for F in `find . -maxdepth 1 -type f -name "*.sh"`;do
	total=`wc -l $F | awk '{print $1}'`
	N=`grep -E -c "^[ 	]*$" $F`
	M=`grep -E -c "^#" $F`
	N=`expr $N + $M`
	total=`expr $total - $N`
	sum=`expr $sum + $total`
	ct=`expr $ct + 1`
done
rez=`expr $sum / $ct`
echo $rez
