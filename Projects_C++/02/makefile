CC=g++
FLAGS=-std=c++17 -Wall -Werror -Wextra -Wno-unused-variable
all: test clean

test: test.o TokenParser.o 
	$(CC) $(FLAGS) -o test test.o TokenParser.o
	./test

test.o: test.cpp TokenParser.h
	$(CC) $(FLAGS) -c test.cpp

TokenParser.o: TokenParser.cpp TokenParser.h
	$(CC) $(FLAGS) -c TokenParser.cpp

clean:    
	rm -rf *.o test