#!/bin/sh

ps -ef | awk '
	BEGIN{
	  sum=0
	  ct=0
	}
	{
	  sum=sum+$2
	  ct++
	}
        END{
	  print sum/ct
	}'
