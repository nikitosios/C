CC=gcc
CFLAGS=-Wall
LDFLAGS=-lncursesw -lpanel -lmenu -lform -lm
SRCS=*.c
EXE=prog

all: clean $(EXE)

$(EXE): $(SRCS)
	$(CC) $(CFLAGS) -o $(EXE) $(SRCS) $(LDFLAGS)

clean:
	rm -rf $(EXE)
