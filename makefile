CC = g++
CFLAGS = -Wall -g -std=c++11

all: parser

parser.o: parser.cpp list.h
	${CC} ${CFLAGS} -c parser.cpp
    
list.o: list.cpp list.h
	${CC} ${CFLAGS} -c list.cpp

parser: parser.o list.o
	${CC} -g parser.o list.o -o parser

clean:
	rm -rf enigma *.o

.PHONY: clean
