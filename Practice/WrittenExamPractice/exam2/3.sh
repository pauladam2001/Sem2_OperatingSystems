#!/bin/bash

awk 'BEGIN{
    	word=0
	ct=0
     }
     {
	for(i=1;i<=NF;i++) {		
		word++		
	}
	ct++
     }
     END{
 	print word/ct	
     }' c.txt				#SAU + NF in loc de for
