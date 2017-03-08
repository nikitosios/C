CC=gcc
CFLAGS=
LDFLAGS=-lm -lGL -lGLEW -lglfw
SRCS=*.c*
EXE=sphere

all: clean $(EXE)

$(EXE): $(SRCS)
	$(CC) $(CFLAGS) -o $(EXE) $(SRCS) $(LDFLAGS)

clean:
	rm -rf $(EXE)
