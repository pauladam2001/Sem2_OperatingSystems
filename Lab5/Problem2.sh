#!/bin/sh

#Using awk substitute all lowercase letters with uppercase letters

awk '{for(i=1;i<=NF;i++)
	printf("%s ",toupper($i))
      printf("\n")}' $1

awk '{print toupper($0)}' $1
