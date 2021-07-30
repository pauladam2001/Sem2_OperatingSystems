#!/bin/sh

df | sed -E "s/%//" | awk '{if($2<1000000){
               			 print $0
           		 }
			 else{
				if($5>80){
					print $0
				}
			 }
	      		}' | sed -E "s/^((.* ){4})([0-9]{2})/\1\3%/"
