#!/bin/sh

grep -E "^(.*:){2}([02468]){5}:" /etc/passwd | awk -F: '{print $5}'
