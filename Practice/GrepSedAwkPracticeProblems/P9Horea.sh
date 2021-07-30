#!/bin/sh

#awk '{print $1}' fileP9.txt | wc -l
#cat fileP9.txt | wc -l
grep -E "^.*" fileP9.txt | wc -l
