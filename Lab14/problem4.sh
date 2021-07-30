#!/bin/bash

if [ $# -lt 1 ];then
	echo "Provide a command"
	exit 1
fi

ps aux | grep -E "(.* +){10}${1}.*$" | while read username line;do
	echo $username is running $1
done 
