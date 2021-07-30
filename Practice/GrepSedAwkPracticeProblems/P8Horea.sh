#!/bin/sh

ls -l | awk '{print $1";"$NF}'  #adaptata, nu stiu cum afisez doar owner rights
