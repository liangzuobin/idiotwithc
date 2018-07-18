CFLAGS = -std=c99 -D_POSIX_C_SOURCE=200809L
CFLAGS += -Wall -pedantic -Wno-parentheses -Ideps
SRC = src/main.c
DEPS = $(wildcard deps/*/*.c)
OBJS = $(SRC:.c=.o) $(DEPS:.c=.o)

all: main

main: $(OBJS)
	$(CC) $^ $(CFLAGS) -o $@

clean:
	rm -f main $(OBJS)

.PHONY: all clean
