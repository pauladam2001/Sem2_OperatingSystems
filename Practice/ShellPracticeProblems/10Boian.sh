#!/bin/sh

D=`date +%Y%m`
T="${D}01000000"
last -t $T | sed -E "s/ .*//" | sort | uniq -c | sort -n -r | while read L U;do
						N=`grep -E "^$U:" /etc/passwd | cut -d: -f5`
						echo $L $N
					done | less

