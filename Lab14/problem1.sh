#!/bin/bash

if [ $# -lt 1 ];then
	echo "Usage $0: arguments"
	exit 1
fi

for arg in $@;do
	if echo $arg | grep -E -q "[0-9]";then
		echo $arg
	fi
done
