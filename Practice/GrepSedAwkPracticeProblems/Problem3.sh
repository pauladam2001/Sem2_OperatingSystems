#!/bin/sh

grep -E "^m" /etc/passwd | awk -F: '$3%7==0 {print $5}'
