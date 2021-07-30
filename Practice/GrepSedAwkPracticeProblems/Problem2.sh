#!/bin/sh

last | awk '{if(index($7, "23:")>0)
		print $1}' | sort | uniq
