CC=gcc
CFLAGS=-Wall
LDFLAGS=-lglut -lGL -lGLU
PROG=game
SRCS=src/*.c
OBJS=*.o

all: $(PROG)

$(PROG): $(OBJS)
	@$(CC) $(CFLAGS) -o $(PROG) $(OBJS) $(LDFLAGS)

$(OBJS): $(SRCS)
	@$(CC) $(CFLAGS) -c $(SRCS)

clean:
	@rm -f $(PROG) *.o
