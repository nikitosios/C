CC=gcc
CFLAGS=--std=c11
LDFLAGS=-lm -lGL -lGLEW -lglfw -lSOIL
SRCS=src/*.c
EXE=learn

all: clean $(EXE)

$(EXE): $(SRCS)
	$(CC) $(CFLAGS) -o $(EXE) $(SRCS) $(LDFLAGS)

clean:
	rm -rf $(EXE)

.PHONY: clean $(EXE)
	./$(EXE)
	rm -rf $(EXE)
