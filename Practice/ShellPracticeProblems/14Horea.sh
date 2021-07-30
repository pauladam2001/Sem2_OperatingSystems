#!/bin/sh

total=$#  #argument count
auxtotal=0
sem=0

i=$1

while read X;do
	while true;do
		N=`grep -E -c "\<$i\>" $X`
		if [ $N -ge 1 ];then
			auxtotal=`expr $auxtotal + 1`
			shift
			i=$1
		else
			break
		fi
		if [ $auxtotal -eq $total ];then
			sem=1
			break
		fi
	done
	
	if [ $sem -eq 1 ];then
		break
	fi
done
