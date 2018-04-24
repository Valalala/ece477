# Walter Rasmussen - Spring 2018
# Makefile for neuralnet. 
TARGET=nn
CC=g++
OBJS=main.o 
CFLAGS=-g -Wall
LIBS=

.PHONY: clean test
#all: test

${TARGET}: ${OBJS}
	${CC} -o ${TARGET} ${OBJS} ${LIBS}

clean:
	rm -f ${OBJS} ${TARGET}


