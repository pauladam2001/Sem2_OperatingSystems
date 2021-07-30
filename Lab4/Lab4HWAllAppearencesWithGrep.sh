#!/bin/bash
# How many times the word "test" appears in the file with grep

#grep -E "test" $1 | wc -l

grep -E "\<test\>" $1 | wc -l
