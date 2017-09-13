CC=gcc
CFLAGS=
LDFLAGS=-lm
SRCS=main.c
EXE=IO

all: clean $(EXE)

$(EXE):
	@$(CC) $(CFLAGS) -o $(EXE) $(SRCS) $(LDFLAGS)

clean:
	@rm -rf $(EXE)
