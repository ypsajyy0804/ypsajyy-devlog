CC      = gcc
CFLAGS  = -Wall -Wextra -Werror
OBJ     = build/vec.o build/main.o
TARGET  = build/vec

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

build/%.o: %.c vec.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f build/vec.o build/main.o build/vec

# .PHONY: clean
