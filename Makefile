.PHONY: test

compile:
	g++ main.cpp -o graphs4 -pedantic -Wall

run: compile
	./graphs4

test: compile
	./run_tests.sh

clean:
	rm graphs4 test/*.myout test/*.diff
