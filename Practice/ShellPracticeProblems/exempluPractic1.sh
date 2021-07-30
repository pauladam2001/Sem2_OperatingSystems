#!/bin/sh

if [ $# -lt 1 ];then
	echo "Introduce a directory as an argument"
	exit 1
fi

if [ $# -gt 1 ];then
	echo "Introduce only a directory as an argument"
	exit 2
fi

sum=0

for F in `find $1 -type f`;do
	if echo $F | grep -E -q "\.c";then
		if file $F | grep -E -q "\<C\>";then
			echo $F
		fi
	else
		if file $F | grep -E -q "\<C\>";then
			N=`cat $F | wc -l`  #daca faceam wc -l $F trebuia si awk '{print $1}'
			sum=`expr $sum + $N`
		fi			
	fi
done

echo $sum

#for F in `find $1 -type f | grep -E "\.c"`;do
#	if file $F | grep -E -q "\<C\>";then
#        	echo $F
#        fi
#done 
