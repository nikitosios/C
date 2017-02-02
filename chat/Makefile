CC=gcc
CFLAGS=-Wall
LDFLAGS=-lpthread -lm
SOURCES=src/*
OBJECTS=build/*.o
PROJDIR=chat-cli
EXECUTABLE=chat-cli
all: clean $(OBJECTS)
	@mkdir -p $(PROJDIR)
	@$(CC) $(CFLAGS) -o $(PROJDIR)/$(EXECUTABLE) $(LDFLAGS)
$(OBJECTS): $(SOURCES)
	@$(CC) $(CFLAGS) -c $(SOURCES)
	@mkdir -p build
	@mv *.o build/
clean:
	@rm -rf build $(PROJDIR) *.o
