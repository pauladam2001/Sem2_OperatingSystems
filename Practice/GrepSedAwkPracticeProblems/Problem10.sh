#!/bin/sh
sed -E "s/[^r]//g" /etc/passwd | sort | uniq

#sed -E "s/[^r]//g" /etc/passwd | sort | uniq -c | sort -n -r

