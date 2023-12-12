#!/bin/sh

for i in $(seq -w 0 99)
do
	./a.out < in/00${i}.txt > out/00${i}.txt
	# echo ${i}
done
