CC=gcc
CFLAGS=-Wall
LDFLAGS=-lncursesw -lform -lpanel
SOURCES=src/*.c
OBJECTS=build/*.o
EXE=$(shell basename `pwd`)
all: clean $(EXE)
$(EXE): $(OBJECTS)
	@mkdir -p $(EXE)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(EXE)/$(EXE) $(LDFLAGS)
$(OBJECTS): $(SOURCES)
	@mkdir -p build/
	@$(CC) $(CFLAGS) -c $(SOURCES)
	@mv *.o build/
clean:
	@rm -rf build/ $(EXE)
