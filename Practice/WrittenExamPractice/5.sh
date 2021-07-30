#!/bin/bash

ctDir=0
cdFis=0


for F in `find . -type d`;do
	if [ -d $F ];then
		ctDir=`expr $ctDir + 1`
		#echo "Da"
		for U in `find $F -maxdepth 1 -type f -name "*.txt"`;do
			ctFis=`expr $ctFis + 1`
			#echo "Fis"
		done
	fi
done

res=`expr $ctFis / $ctDir`
echo $res
