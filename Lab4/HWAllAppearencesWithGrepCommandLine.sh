#!/bin/sh
# How many times a given word appears in a given file

#grep -E "$1" $2 | wc -l

#n=""
n=`grep -E "$1" $2 | wc -l`
echo "We found $n occurences"
