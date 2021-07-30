#!/bin/bash

touch aux.txt

for F in `find $1 -type f`;do
	echo $F | sed -E "s/(.*\/)//g" >> aux.txt
done
echo `cat aux.txt | sort | uniq -c | sort -n -r | awk '{print $2}'`
rm aux.txt
