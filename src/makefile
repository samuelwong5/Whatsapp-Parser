CC = g++
CFLAGS = -Wall -g -std=c++11

all: parser

main.o : main.cpp parser.h util/util.h
	${CC} ${CFLAGS} -c main.cpp    

parser.o: parser.cpp parser.h util/list.h util/util.h
	${CC} ${CFLAGS} -c parser.cpp

parser: main.o parser.o util/list.o util/util.o
	${CC} -g main.o parser.o util/list.o util/util.o -o parser

clean:
	rm -rf parser *.o

.PHONY: clean
