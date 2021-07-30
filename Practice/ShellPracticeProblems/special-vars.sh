#!/bin/bash
echo Command: $0
echo First four args: $1 $2 $3 $4
echo All args: $@
echo Arg count: $#

true
echo Command true exited with exit code $?

false
echo Command false exited with exit code $?
