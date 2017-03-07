CC=gcc
CFLAGS=
LDFLAGS=-lm -lGL -lGLEW -lglfw
EXE=learning_opengl
SRCS=src/*.c*

all: $(EXE)

$(EXE): $(SRCS) clean
	@$(CC) $(CFLAGS) -o $(EXE) $(SRCS) $(LDFLAGS)

clean:
	@rm -f $(EXE)
