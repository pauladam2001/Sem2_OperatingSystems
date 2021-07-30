#!/bin/sh

for F in `find $1`; do
	if [ -L $F ];then
		if [ ! -e `find -L $F` ];then
			echo $F does not exist
		fi
	fi
done
