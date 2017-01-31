CC=gcc
SOURCES=main.c
CFLAGS=-Wall
LDFLAGS=-lssh -lncurses
EXECUTABLE=ssh

all: clean
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SOURCES) $(LDFLAGS)

clean:
	rm -f $(EXECUTABLE)
