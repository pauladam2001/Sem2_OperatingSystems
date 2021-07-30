#!/bin/sh

awk '{if(NR%2==1){
      	s=0
	ct=0
	for(i=1;i<=NF;i++){
		if(i%2==0){
			s=s+$i
			ct++
		}
	}
	if(ct!=0){
		print NR" "s/ct
	}
      }	
     }' PracticeProblemAwk.txt
