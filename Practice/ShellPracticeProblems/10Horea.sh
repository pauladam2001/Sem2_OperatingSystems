#!/bin/sh

process=$1

while true; do
	N=`ps | grep -E -c "\<$process\>"` 
	if [ $N -ge 1 ];then
		killall $process
		echo Killed process $process
	fi
done
