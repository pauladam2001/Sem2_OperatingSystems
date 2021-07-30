#!/bin/sh

last | awk '{if(index($3, "economica")>0)
		if(index($4, "Sun")>=0)
			print $1}' | sort | uniq
