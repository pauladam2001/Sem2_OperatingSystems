#!/bin/sh

ls -l | grep -E "^-r..r..r" | awk '{print $NF}'
