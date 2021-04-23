CC = gcc
CFLAGS = -g -Wall

all: simple-shell.out

simple-shell.out: src/*.c
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	$(RM) simple-shell.out