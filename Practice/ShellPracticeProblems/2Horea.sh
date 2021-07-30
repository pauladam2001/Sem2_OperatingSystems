#!/bin/sh

while true; do
	read X
	if test "$X" == "stop";then
		break
	fi
	
	if [ -f $X ];then
		if file $X;then		#OR if echo $X | grep -E -q "*.txt"; then
			cnt=`head -1 $X | awk '{print NF}'`
			echo $cnt
		fi
	fi
done
