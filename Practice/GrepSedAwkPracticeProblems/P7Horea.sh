#!/bin/sh

last | awk '{print $1}' | sort | uniq -c | sort -n -r
