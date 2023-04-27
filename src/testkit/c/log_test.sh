#! /bin/sh
#! /bin/bash

for i in {1..100}
do
	sleep 0.1
	./log_tcp_client 127.0.0.1 $i&
done
