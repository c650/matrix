CC=g++
CFLAGS=-Wall -Werror --std=c++11

SRC=*.cpp
OUT=matrix.out

build:
	${CC} ${CFLAGS} -o ${OUT} ${SRC}

.PHONY:
	clean

clean:
	rm matrix.out
