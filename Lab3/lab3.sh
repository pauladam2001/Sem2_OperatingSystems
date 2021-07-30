#!/bin/sh
#using sed select all the names containing rares from the /etc/passwd file
sed '/!/rares/d' /etc/passwd 
