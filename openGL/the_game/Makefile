CC=gcc
CFLAGS=
LDFLAGS=-lm -lGLEW -lglfw -lGL -lSOIL
SRCS=src/*.c
EXE=the_game

all: clean $(EXE)

$(EXE): $(SRCS)
	$(CC) $(CFLAGS) -o $(EXE) $(SRCS) $(LDFLAGS)

clean:
	rm -rf $(EXE)
