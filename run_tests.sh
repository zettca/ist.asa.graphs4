#!/bin/bash

for (( i = 1; i <= 5; i++ )); do
	./graphs4 < test/$i.in > test/$i.myout
	diff test/$i.myout test/$i.out > test/$i.diff
	printf "TEST $i "
	if [ -s test/$i.diff ]; then
		echo -ne "\x1b[31;1m"
		echo "FAIL"
	else
		echo -ne "\x1b[32;1m"
		echo "PASS"
		rm test/$i.myout test/$i.diff
	fi
	echo -ne "\x1b[0m"
done
