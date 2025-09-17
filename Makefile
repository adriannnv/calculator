CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lm
TARGET = calculator
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
DEPS = $(wildcard *.h)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)
