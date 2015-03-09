CC = g++
CFLAGS = -Wall -g -std=c++11

all: util.o list.o

list.o: list.cpp list.h
	${CC} ${CFLAGS} -c list.cpp

util.o: util.cpp util.h
	${CC} ${CFLAGS} -c util.cpp

clean:
	rm -rf *.o

.PHONY: clean
