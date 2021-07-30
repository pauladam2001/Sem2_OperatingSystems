#!/bin/sh

ls -l | awk '{if($5>100)print $9}'
