CC=g++
CFLAGS=-std=c++11 -Wall -O3

##### SOKOBAN
r1: mysok.h r1.cpp
	$(CC) $(CFLAGS) r1.cpp -o $@

t1: mysok.h testsok.h t1.cpp
	$(CC) $(CFLAGS) t1.cpp -o $@
