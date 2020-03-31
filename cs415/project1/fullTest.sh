#!/bin/bash
set -x

for part in {1,2,3,4,5}
do
	./goodtest.sh $part
	sleep 3
	./badtest.sh $part
	sleep 3
	./valtest.sh $part
	sleep 3
done

./part4 test.txt
sleep 5
./part5 test.txt
