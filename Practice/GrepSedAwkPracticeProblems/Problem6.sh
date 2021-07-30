#!/bin/sh

grep -E "^(.*:){2}([2][3])+([0-9][^:]*){3}:" /etc/passwd | awk -F: '{print $5}'

