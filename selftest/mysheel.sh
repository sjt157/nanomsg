#!/bin/bash

BASE="$(cd "$(dirname "$0")"&&pwd)"
PUB=$BASE/pubserver
SUB=$BASE/pubclient

URL="tcp://127.0.0.1:1234"

echo "start to start pubclient"
$PUB tcp://127.0.0.1:1234 &
for((i=0;i<10;i++))
	do
	echo "start client$i"
	$SUB client$i $URL &
	sleep 1
done

sleep 20

echo "kill all process and exit"

for pid in `jobs -p`
do
	echo "kill $pid"
	kill $pid
done

wait
