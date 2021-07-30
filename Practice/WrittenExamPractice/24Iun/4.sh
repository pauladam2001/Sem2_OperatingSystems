#!/bin/bash

for D in `find . -type d`;do
	sem=0
	if ls $D | grep -E -q ".+\.mp3";then
		sem=1
	fi
	if [ $sem -eq 1 ];then
		echo $D
	fi
done
