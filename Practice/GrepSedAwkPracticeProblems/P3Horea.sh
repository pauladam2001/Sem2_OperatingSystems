#!/bin/sh

cut -d: -f5,6 /etc/passwd | grep -E "[^:]*/gr[0-9]{2}[13579]/" | awk -F/ '{print $1" "$6}'
