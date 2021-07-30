#!/bin/bash

sum=0
ct=0

for F in `find . -maxdepth 1 -type f -name "*.sh"`;do
	#N=`grep -E "^[^#]+" $F | wc -l | awk '{print $1}'`
	N=`grep -E -c "^[^#]+" $F`
	echo "$F has $N"
	sum=`expr $sum + $N`
	#echo $sum
	ct=`expr $ct + 1`
	#echo $ct
done

#echo $sum/$ct
rez=`expr $sum / $ct`
echo $rez
