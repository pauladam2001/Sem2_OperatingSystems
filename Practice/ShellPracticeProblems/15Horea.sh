#!/bin/sh

users=`cat /etc/passwd | awk -F: '{print $1}'`
users_ips=`cat last | awk '{print $1" "$3}'`

for user in $users;do
	touch $user.txt
	for ip in $users_ips;do
		N=`echo $ip | grep -E "\<$user\>" | awk '{print $1}'`
		if [ $N == $user ];then
			echo "ok"
			echo $ip | grep -E "\<$user\>" | awk '{print $2}' >> $user.txt
		fi
	done
done
