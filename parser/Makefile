CC=gcc
CFLAGS=-Wall -O2
LDFLAGS=-lm -lcurl
SRCS=src/*.c
EXE=parser

all: clean $(EXE)

$(EXE): $(SRCS)
	@mkdir -p build/$(EXE)
	@$(CC) $(CFLAGS) -o build/$(EXE)/$(EXE) $(SRCS) $(LDFLAGS)

clean:
	@rm -rf build/$(EXE)/$(EXE)

execute: build/$(EXE)/$(EXE)
	@cd build/$(EXE) && ./$(EXE)

.PHONY: clean $(EXE) execute
