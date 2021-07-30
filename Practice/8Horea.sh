#!/bin/sh

touch 8Horea.txt

for F in `find $1 -type f`;do
	echo $F | sed -E "s/(.*\/)//" >> 8Horea.txt
done

echo `cat 8Horea.txt | sort | uniq -c | sort -n -r`

rm 8Horea.txt
