#!/bin/sh
if ! test -f a.txt || (test -f a.txt && ! test -r a.txt); then
	echo a.txt is not a file or is not readable
else
	echo a.txt is a file and is readable
fi
