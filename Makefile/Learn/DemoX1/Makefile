# Makefile

SRCS = main.c foo.c bar.c
OBJS = $(SRCS:.c=.o)
APP  = prog

CC = gcc
CFLAGS = -Wall -g

all:$(APP)

$(APP):$(OBJS)
	$(CC) $(LDFLAGS) $(LIBRARY) -o $@ $^

%.o:%.c
	$(CC) -c $(CFLAGS) -o $@ $<

.PHONY: all clean
clean:
	-rm -rf $(OBJS) $(APP)
