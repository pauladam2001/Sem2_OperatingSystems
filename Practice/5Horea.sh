#!/bin/sh

if [ -f headers.txt ];then
	rm headers.txt
	touch headers.txt
else
	touch headers.txt
fi

touch aux

for A in $@;do
	filetype=`file $A`
	okay=`echo $filetype | grep -E -c "C source"`

	if [ $okay -ge 1 ];then
		`grep -E "^#include <.+>$" $A >> aux`
	fi
done

cat aux | sort | uniq >> headers.txt

rm aux
