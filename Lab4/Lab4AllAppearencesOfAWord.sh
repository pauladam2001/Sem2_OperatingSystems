#!/bin/sh
# How many times the word "test" appears in the file

awk '{
for(i=1;i<=NF;i++){
  if(index($i,"test")>0){
    n++;
  }
}
}END{
printf("We found %d occurences\n", n);
}' $1
