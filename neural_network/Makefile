CC=gcc
CFLAGS=-Wall -Wextra -O2
LDFLAGS=-lm
SRCS=src/*.c
EXE=nn

all: $(EXE)

$(EXE): $(SRCS)
	@mkdir -p build/$(EXE)
	@$(CC) $(CFLAGS) $(SRCS) -o build/$(EXE)/$(EXE) $(LDFLAGS)

clean:
	@rm -rf build

execute:
	@sh -c "cd build/$(EXE)/ && ./$(EXE)"

.PHONY: all execute
