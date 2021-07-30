#!/bin/bash

ps -ef | grep -E "^root" | awk '{print $6}' | sort | uniq 
