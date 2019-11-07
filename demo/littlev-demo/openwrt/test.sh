#!/bin/sh

SPOT="35.172.250.125"
#DUT="192.168.0.19"
DUT="192.168.2.5"

scp ubuntu@$SPOT:/home/ubuntu/littlev-demo/bin/demo bin/demo-new

scp bin/demo-new root@$DUT:/root/demo
#sleep 2
#ssh root@$DUT /root/demo

echo "> DONE"

