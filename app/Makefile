CC=gcc
CFLAGS=-Wall
LDFLAGS=`pkg-config gtk+-3.0 --cflags --libs`
EXE=app
all:
	$(CC) $(CFLAGS) -o $(EXE) main.c $(LDFLAGS)
clean:
	rm -rf $(EXE)
