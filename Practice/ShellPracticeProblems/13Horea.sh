#!/bin/sh

s=""
email=@scs.ubbcluj.ro
totallines=`cat $1 | wc -l`
currentline=1

cat $1 | while read X;do
	if [ $currentline -eq $totallines ];then
		s=$s$X$email
		echo $s
	else
		s=$s$X$email,
		currentline=`expr $currentline + 1`
	fi
	
done

#OR for X in `cat $1`;do
