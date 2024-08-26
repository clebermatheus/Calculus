CFILES=src/**.c
HFILES=src/**.h
CFLAGS=-Wall -g -std=c99 -Wpedantic -lm -lncurses

all:
	mkdir -p bin
	gcc $(CFILES) -o bin/limit $(CFLAGS)

clean:
	rm -rf bin
