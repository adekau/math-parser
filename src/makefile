OUTPUT = ../mp
CC = gcc
DEPS = linkedlist.h tokenizer.h
SRCFOLDER = src
OBJ = linkedlist.o tokenizer.o
CFLAGS = -Wall -Wpedantic --std=c99

%.o: %.c ${DEPS}
	${CC} -c -o $@ $< ${CFLAGS}

${OUTPUT}: ${OBJ}
	${CC} -o $@ $^ ${CFLAGS}

.PHONY: clean

clean:
	rm ${OUTPUT} *.o
