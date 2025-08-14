CC = gcc
CFLAGS = -Wall -Wextra
TARGET = calculator
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
DEPS = $(wildcard *.h)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)