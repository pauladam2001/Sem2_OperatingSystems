#!/bin/sh

ps -ef | grep -E -v -i "^[a-z]{4}[0-9]{4}" | awk '{print $1, $2, $8}'
#ps -ef | grep -E -v -i "^[a-z]{4}[0-9]{4}" | cut -f1,2,8 #? cum folosesc cut?

