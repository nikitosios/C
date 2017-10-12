CC=gcc
CFLAGS=-Wall -Wextra -O2 -g
LDFLAGS=-lm -lcurl
SRCS=src/*.c
EXE=repeat_words

all: clean $(EXE)

$(EXE): $(SRCS)
	@rm -rf build
	@mkdir -p build/$(EXE)
	@$(CC) $(CFLAGS) -o build/$(EXE)/$(EXE) $(SRCS) $(LDFLAGS)

clean:
	@rm -rf build

execute:
	@sh -c "cd build/$(EXE) && ./$(EXE)"

.PHONY: clean $(EXE) execute
