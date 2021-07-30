#!/bin/bash

sum=0
ct=0

for F in `find . -maxdepth 1 -type f -name "*.txt"`;do
	total=`wc -l $F | awk '{print $1}'`
	sum=`expr $sum + $total`
	ct=`expr $ct + 1`	
done
rez=`expr $sum / $ct`
echo $rez
