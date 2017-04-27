compile:
	g++ main.cpp -o graphs4 -pedantic -Wall

run: compile
	./graphs4

test:
	./run_tests.sh

clean:
	rm graphs4 test/diff/* test/oute/*
