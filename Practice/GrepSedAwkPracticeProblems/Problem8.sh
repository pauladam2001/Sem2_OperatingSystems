#!/bin/sh

ps -ef | grep -E "^r" | sort | uniq | sed -E "s/([aeiou])/\1\1/gi"
