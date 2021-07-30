#!/bin/sh

cat fileP12.txt | awk 'BEGIN{
			vowel=0
			consonant=0
		       }
		       {
			if($NF ~ /[aeiouAEIOU]$/){
				vowel=vowel+1;
			}
			else{
				consonant=consonant+1;
			}
		       }
		       END{
			print vowel" "consonant;
		       }'
