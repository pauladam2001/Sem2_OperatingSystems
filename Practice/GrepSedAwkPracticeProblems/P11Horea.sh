#!/bin/sh

grep -E ".*gr[0-9]{1,}" /etc/passwd | awk -F: '{print $6}' | awk -F/ '{print $6}' | uniq -c
