#!/bin/sh
# Switch first column with last column using sed

sed -E "s/^([^ ]+) (.*) ([^ ]+)$/\3 \2 \1/" f.txt
