#!/bin/sh

if [ $# -lt 2 ];then
	echo "Introduce at least 2 arguments"
	exit 1
fi

sequence=$1

shift

for A in $@;do
	if [ -f $A ];then
		N=`grep -E "$sequence" $A | wc -l`
		if [ $N -ge 1 ];then
			echo "File $A contains the sequence"
		fi
	fi
	if [ -d $A ];then
		for F in `find $A -maxdepth 1`;do                #OR with -name
			if echo $F | grep -E -q "^$sequence$";then
				echo "$A contains the sequence in the name"
			fi
		done
	fi
done
