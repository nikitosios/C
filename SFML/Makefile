CC=g++
CFLAGS=-Wall
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
SOURCES=src/*.cpp
OBJECTS=build/*.o
PROGDIR=sfml-prog
EXECUTABLE=sfml-prog
all: $(OBJECTS)
	@mkdir -p $(PROGDIR)
	@$(CC) $(CFLAGS) -o $(PROGDIR)/$(EXECUTABLE) $(SOURCES) $(LDFLAGS)
$(OBJECTS): $(SOURCES)
	@mkdir -p build
	@mkdir -p $(EXECUTABLE)
	@$(CC) $(CFLAGS) -c $(SOURCES)
	@mv *.o build
clean:
	rm -rf $(PROGDIR) build
