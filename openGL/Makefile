CC=gcc
CFLAGS=-Wall
LDFLAGS=-lglut -lGLU -lGL
EXECUTABLE=opengl

all: clean
	@$(CC) $(CFLAGS) -o $(EXECUTABLE) main.c $(LDFLAGS)

clean:
	@rm -f $(EXECUTABLE)
