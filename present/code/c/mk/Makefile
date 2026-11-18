CC = gcc
CFLAGS = -Wall -Wextra -Werror

build/mkapp: build/main.o build/util.o | build
	$(CC) $(CFLAGS) -o $@ $^

build/main.o: main.c util.h | build
	$(CC) $(CFLAGS) -c main.c -o $@

build/util.o: util.c util.h | build
	$(CC) $(CFLAGS) -c util.c -o $@

build:
	mkdir -p build

clean:
	rm -rf build

.PHONY: clean
