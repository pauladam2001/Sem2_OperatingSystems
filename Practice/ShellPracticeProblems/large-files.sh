#!/bin/sh
#All the files in the directory given as first command line argument, largen in size than the second command line argument

D=$1
S=$2

find $D -type f | while read F; do
	N=`ls -l $F | awk '{print $5}'`
	if test $N -gt $S; then
		echo $F
	fi
done
