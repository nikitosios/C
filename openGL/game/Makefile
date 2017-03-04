CC=gcc
CFLAGS=-Wall
LDFLAGS=-lm -lGL -lGLEW -lglfw
SRCS=src/*.c*
PROJDIR=game
EXE=game

all: clean $(EXE)

$(EXE): $(SRCS)
	$(CC) $(CFLAGS) -o $(PROJDIR)/$(EXE) $(SRCS) $(LDFLAGS)

clean:
	rm -rf $(PROJDIR)/$(EXE)
