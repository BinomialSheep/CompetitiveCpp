#!/bin/sh

for i in $(seq -w 0 999)
do
	./a.out < in/0${i}.txt > output.txt 2>> debug.txt
	# echo ${i}
done
