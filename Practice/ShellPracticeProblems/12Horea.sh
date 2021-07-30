#!/bin/sh

for F in `find $1 -type f -perm /u=w -perm /g=w -perm /o=w`;do
	echo $F
	chmod u-w,o-w,g-w $F
done
