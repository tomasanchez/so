# C Makefile using gcc, gdb and valgrind. Modified version of Makefile using g++ & gdb by Roberto Nicolas Savinelli <rsavinelli@est.frba.utn.edu.ar>
# Tomas Agustin Sanchez <tosanchez@est.frba.utn.edu.ar>

CC = gcc
CFLAGS = -Wall -Wextra -g3
LIBS = -lcommons -pthread
INCLUDES = -I ./include/
SOURCES = ./src/*.c

LOG = leaks.log
OUTPUT = gamecard.exe

.PHONY: compile debug clean vg hg

compile:
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES) $(LIBS) -o $(OUTPUT)

debug:
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES) $(LIBS) -o $(OUTPUT) && gdb -se $(OUTPUT)

vg:
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES) $(LIBS) -o $(OUTPUT) && valgrind --leak-check=yes --log-file="$(LOG)" --track-origins=yes ./$(OUTPUT)

hg:
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES) $(LIBS) -o $(OUTPUT) && valgrind --tool=helgrind --log-file="threads.log" ./$(OUTPUT)

clean:
	$(RM) ./$(OUTPUT)  && $(RM) ./$(LOG)
