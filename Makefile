# C Makefile using gcc and gdb

CC = gcc
CFLAGS = -std=c99 -Wall
INCLUDES = -I ./include/ -I ./lib/include
SOURCES = ./src/*.c ./lib/src/*.c


OUTPUT = test

.PHONY: compile debug clean

compile:
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES) -lcommons -o $(OUTPUT)

debug:
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES) -g3 -o $(OUTPUT) && gdb -se $(OUTPUT)

clean:
	$(RM) ./$(OUTPUT)
