CXX=clang++
CXX_FLAGS=-std=c++20 -g -O0 -Wall -Wextra -Werror -pedantic -Iincludes/

exec: bin/exec

bin/exec: ./src/driver.cc ./src/illini_book.cc ./src/utilities.cc
	${CXX} ${CXX_FLAGS} src/driver.cc src/illini_book.cc ./src/utilities.cc -o bin/exec

# bin/tests: tests/tests.cc includes/illini_book.hpp src/illini_book.cc
# 	${CXX} ${CXX_FLAGS} tests/tests.cc src/solution.cc -o bin/tests

.DEFAULT_GOAL := exec
.PHONY: clean exec

clean:
	rm -rf bin/*
