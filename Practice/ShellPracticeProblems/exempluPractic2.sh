#!/bin/sh

if [ $# -lt 1 ];then
	echo "Directory name as argument"
	exit 1
fi
if [ $# -gt 1 ];then
	echo "Only a directory as argument"
	exit 2
fi

for F in `find $1 -type f`;do
	if echo $F | grep -E -q -v "\.txt";then
		echo $F
	fi
	if echo $F | grep -E -q "\.txt";then
		sed -E "y/aeiou/AEIOU/" $F
	fi
done
