for (( i = 1; i <= 5; i++ )); do
	./graphs4 < test/in/$i > test/oute/$i
	colordiff test/oute/$i test/out/$i > test/diff/$i
	printf "TEST $i "
	if [ -s test/diff/$i ]; then
		echo -ne "\x1b[31;1m"
		echo "FAIL"
	else
		echo -ne "\x1b[32;1m"
		echo "PASS"
	fi
	echo -ne "\x1b[0m"
done
