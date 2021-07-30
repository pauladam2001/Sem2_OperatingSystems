#!/bin/sh

ps -ef | grep -E "\<ex[13579]{3}\>" | grep -E "^(.* )[0-9]{3} " | awk '{print $1, $2}'
