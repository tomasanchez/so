# C Makefile using gcc, gdb and valgrind. 
# Modified version of Makefile using g++ & gdb by Roberto Nicolas Savinelli <rsavinelli@est.frba.utn.edu.ar>
# Tomas Agustin Sanchez <tosanchez@est.frba.utn.edu.ar>

CC = gcc
CFLAGS = -Wall -Wextra -g3
LIBS = -lcommons -lreadline
INCLUDES = -I ./include/
SOURCES = ./src/*.c

OUTPUT = basics.exe
LEAKS = log/leaks.log
HELGRIND = log/threads.log

.PHONY: compile

compile:
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES) $(LIBS) -o $(OUTPUT)

run:
	$(MAKE) compile && ./$(OUTPUT)

debug:
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES) $(LIBS) -o $(OUTPUT) && gdb -se $(OUTPUT)
	
leaks:
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES) $(LIBS) -o $(OUTPUT) && valgrind --leak-check=yes --log-file="$(LEAKS)" --track-origins=yes ./$(OUTPUT)

threads:
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES) $(LIBS) -o $(OUTPUT) && valgrind --tool=helgrind --log-file="$(HELGRIND)" ./$(OUTPUT)

clean:
	$(RM) ./$(OUTPUT) && $(RM) ./$(LOG)