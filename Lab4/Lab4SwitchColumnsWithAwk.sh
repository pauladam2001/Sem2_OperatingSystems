#!/bin/sh

awk '{
printf("%s ",$NF);
for(i=2;i<=NF-1;i++){
  printf("%s ",$i);
}
if(NF > 1){
  printf("%s\n", $1);
}
}' f.txt
