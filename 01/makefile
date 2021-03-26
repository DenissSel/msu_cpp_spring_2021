CC=g++
FLAGS=-std=c++17 -Wall -Werror -Wextra -Wno-unused-variable
all: test clean

test: test.o Allocator.o 
	$(CC) $(FLAGS) -o test test.o Allocator.o
	./test

test.o: test.cpp test.h Allocator.h
	$(CC) $(FLAGS) -c test.cpp

Allocator.o: Allocator.cpp Allocator.h
	$(CC) $(FLAGS) -c Allocator.cpp

clean:    
	rm -rf *.o test