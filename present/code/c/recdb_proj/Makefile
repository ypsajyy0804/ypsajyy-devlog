CC =gcc
CFLAGS = -Wall -Wextra -Werror
OBJ1 = build/recdb.o build/main.o
OBJ2 = recdb.h
TARGET = build/recdb

$(TARGET): $(OBJ1) | build
	$(CC) $(CFLAGS) -o $@ $^

build/%.o: %.c $(OBJ2) | build
	$(CC) $(CFLAGS) -c $< -o $@

build:
	mkdir -p build

clean:
	rm -rf build

.PHONY: clean
