CC=gcc
CFLAGS=-Wall
LDFLAGS=-lglut -lGL -lGLU -lSOIL
PROGDIR=game
PROG=game
SRCS=src/*.c
OBJS=*.o

all: clean $(PROG)

$(PROG): $(OBJS)
	@mkdir -p $(PROGDIR)
	@$(CC) $(CFLAGS) -o $(PROGDIR)/$(PROG) $(OBJS) $(LDFLAGS)

$(OBJS): $(SRCS)
	@$(CC) $(CFLAGS) -c $(SRCS)

clean:
	@rm -f $(PROGDIR)/$(PROG) *.o
