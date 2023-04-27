#! /bin/sh
#! /bin/bash

for((i=0;i<$1;i++))
do
	sleep 0.1
	./log_tcp_client 192.168.75.11 $i $2 $3&
done
