CC=gcc
CFLAGS=-Wall
LDFLAGS=-lGL -lGLEW -lglfw
EXE=glsl
SRCS=src/*.c*

all: $(EXE)

$(EXE): $(SRCS) clean
	@$(CC) $(CFLAGS) -o $(EXE) $(SRCS) $(LDFLAGS)

clean:
	@rm -f $(EXE)
