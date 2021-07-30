#!/bin/sh

cat fileP12.txt | uniq -c | awk '{print $1}' | awk 'BEGIN{
						sum=0
					      }
					      {
						if($1>1)
						   sum=sum+$1
					      }
					      END{
						print sum
					      }'

#OR uniq -c fileP12.txt
