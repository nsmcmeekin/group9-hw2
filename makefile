#modify this makefile so that it will work for this new assignment
CC=g++
DEPS = starter.h

main: main.cpp
	g++ -o main main.cpp

clean: 
	rm -f main
