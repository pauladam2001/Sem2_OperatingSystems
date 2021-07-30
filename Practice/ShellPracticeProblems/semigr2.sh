#!/bin/sh

sequence=$1
sum=0

for F in $@;do
        if [ $F != $1 ];then
                for file in `find $F -maxdepth 1 -type f -name "*$sequence*"`;do
                        M=`cat $file | grep -E "$sequence" | wc -l`
                        if [ $M -ge 1 ];then
                        	sum=`expr $sum + 1`
                        fi
                done
                echo $sum
                sum=0
        fi
done
