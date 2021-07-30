#!/bin/sh

grep -E -i "^[^a-z0-9]*$" fileP5.txt | wc -l
