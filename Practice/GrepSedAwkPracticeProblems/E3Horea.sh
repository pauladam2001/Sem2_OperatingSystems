#!/bin/sh

cut -d: -f1 /etc/passwd | sed "y/0123456789/1234567890/"
