CC=gcc
CFLAGS=-Wall
LDFLAGS=-lglut -lGL -lGLU
PROG=lighting
SRCS=main.c

all: $(PROG)

$(PROG): $(SRCS)
	@$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LDFLAGS)

clean:
	@rm -f $(PROG)
