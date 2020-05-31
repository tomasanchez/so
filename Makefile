# C Makefile using gcc and gdb

CC = gcc
CFLAGS = -Wall -Wextra
INCLUDES = -I ./include/
SOURCES = ./src/*.c


OUTPUT = team

.PHONY: compile debug clean

compile:
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES) -lcommons -o $(OUTPUT)

debug:
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES) -g3 -o $(OUTPUT) && gdb -se $(OUTPUT)

clean:
	$(RM) ./$(OUTPUT)
