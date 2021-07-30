#!/bin/sh

cut -d: -f5,6 /etc/passwd | grep -E "/gr[0-9]{3,}/" | awk -F/ '{print $1"-"$7"-"$6}'
