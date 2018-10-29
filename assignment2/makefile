# specify compiler being used
CC = gcc

# specify compiler options / flags
CFALGS = -Wall -g -pedantic

# targets and dependencies
list: list.c
	$(CC) $(CFLAGS) -o list.o list.c

test: list.c list_simple_tester.c list.h
	$(CC) list.c list_simple_tester.c