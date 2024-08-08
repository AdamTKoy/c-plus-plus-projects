CXX=clang++
CXX_FLAGS=-std=c++20 -g -O0 -Wall -Wextra -Werror -pedantic -Iincludes/

exec: bin/exec

bin/exec: src/driver.cc src/cord.cc src/cord-utilities.cc
	${CXX} ${CXX_FLAGS} src/driver.cc src/cord.cc src/cord-utilities.cc -o bin/exec


.DEFAULT_GOAL := exec
.PHONY: clean exec

clean:
	rm -rf bin/*
