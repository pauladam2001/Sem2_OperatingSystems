#!/bin/sh

sed -E "s/[a-zA-Z0-9 ]//gi" /etc/passwd | sort | uniq
