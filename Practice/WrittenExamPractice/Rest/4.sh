#!/bin/bash

#sem=1

#for D in `find . -maxdepth 0 -type d`;do
	#for F in `find . -type f -name "*.c"`;do
#		if [ sem = 1 ];then
#			sem=`expr $sem + 1`
#		fi
#		if [ sem != 1 ];then
#			echo $F
#		fi
	#	echo $F | grep -E -o "/.+/"
	#done
#done

for D in `find . -mindepth 1 -type d`;do
	for F in `find $D -maxdepth 1 -type f -name "*.c"`;do
		echo $D
	done
done
