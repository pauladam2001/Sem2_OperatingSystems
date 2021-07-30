#!/bin/sh

for file1 in `find $1 -type f`;do
	for file2 in `find $1 -type f`;do
		if [ $file1 != $file2 ];then
			sum1=`md5sum $file1 | awk '{print $1}'`
			sum2=`md5sum $file2 | awk '{print $1}'`
			if [ $sum1 == $sum2 ];then
				echo "$file1 is the same with $file2"
			fi
		fi
	done	
done
