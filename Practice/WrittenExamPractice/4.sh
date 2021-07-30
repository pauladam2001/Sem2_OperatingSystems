#!/bin/bash

ps aux | awk '{print $1}' | sort | uniq -c | while read n u;do
						N=`grep -E "^$u" /etc/passwd | awk -F: '{print $5}'`
						echo $n $N
					     done
