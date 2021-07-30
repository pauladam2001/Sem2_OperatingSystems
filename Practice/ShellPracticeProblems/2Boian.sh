#!/bin/sh

dir=$1
nrLines=$2

for F in `find $1 -type f -name "*.sh"`;do #OR find $dir -name "*.c" -type f |while read F;do
	nrCurrLines=`wc -l $F | awk '{print $1}'`	#wc -l returneaza si numele fisier
	if [ $nrCurrLines -gt $nrLines ];then
		echo $F	
	fi
done
