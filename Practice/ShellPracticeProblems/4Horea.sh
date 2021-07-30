#!/bin/sh

touch 4Horea.txt

for A in $@; do
	if [ -f $A ];then
		file=$A
		size=`ls -l $A | awk '{print $5}'`
		echo $size $file >> 4Horea.txt
	fi
done

echo `cat 4Horea.txt | sort -n`

rm 4Horea.txt
