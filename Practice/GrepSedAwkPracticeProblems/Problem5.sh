#!/bin/sh

grep -E "^[^:]*([8][8]):" /etc/passwd | awk -F: '{print $5}'

