# Makefile

SRCS = main.c foo.c bar.c
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)
APP  = prog

CC = gcc
CFLAGS = -Wall -g

all:$(APP)

$(APP):$(OBJS)
	$(CC) $(LDFLAGS) $(LIBRARY) -o $@ $^

%.o:%.c
	$(CC) -c $(CFLAGS) -o $@ $<

%.d: %.c
	$(CC) -M $(CPPFLAGS) $< > $@

-include $(DEPS)

.PHONY: all clean
clean:
	-rm -rf $(OBJS) $(DEPS) $(APP)
