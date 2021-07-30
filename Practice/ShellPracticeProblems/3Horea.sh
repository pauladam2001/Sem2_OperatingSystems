#!/bin/sh

i=0
j=1

for A in $@;do
	i=$((i+1))
	if [ $i -eq 1 ];then
		filee=$A
	fi
	if [ $i -eq 2 ];then
		wordd=$A
		N=`grep -E -o "\<$wordd\>" $filee | wc -l`
		if [ $N -ge 3 ];then
			echo The word $wordd appears at least 3 times in the file $filee
		else
			echo Condition not met for the pair: $filee, $wordd
		fi
		i=0
	fi	
done
