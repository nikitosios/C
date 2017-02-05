CC=gcc
CFLAGS=-Wall
LDFLAGS=-lglut -lGLU -lGL
SOURCES=src/*.c
OBJECTS=build/*.o
PROJDIR=game
EXECUTABLE=game

all: clean $(OBJECTS)
	@mkdir -p $(PROJDIR)
	@$(CC) $(CFLAGS) -o $(PROJDIR)/$(EXECUTABLE) build/* $(LDFLAGS)

$(OBJECTS): $(SOURCES)
	@$(CC) $(CFLAGS) -c $(SOURCES)
	@mkdir -p build
	@mv *.o build

clean:
	@rm -rf build *.o
