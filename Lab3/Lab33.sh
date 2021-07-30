#!/bin/sh
# From all the arguments that are directories to list all the files that are binary files
for a in $@
do
 # echo "a:" $a
  if test -d $a; then
    #echo "$a is a directory"
    ls -1 $a | while read v
    do
   #   echo "$v in $a"
      if test -f $a/$v; then
        #echo "$v is a file"
        if file $a/$v | grep -q "executable"; then
	  echo "$v is a binary file"
	fi
      fi
    done
  fi
done
