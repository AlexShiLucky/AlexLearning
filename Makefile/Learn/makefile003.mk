
SOURCE = $(wildcard *.c)
TARGET = $(patsubst %.c,%,$(SOURCE))

CC = gcc
CFLAGS = -Wall -g

all:$(TARGET)

$(TARGET): %:%.c
	$(CC) $< $(CFLAGS) -o $@

.PHONY: clean all
clean:
	-rm -rf $(TARGET)
