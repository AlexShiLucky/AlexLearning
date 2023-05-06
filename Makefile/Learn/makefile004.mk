SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))
APPS = $(SRCS:%.c=%)

CC = gcc
CFLAGS = -Wall -g

$(info $(OBJS))
$(info $(APPS))

all: $(APPS)

#$(APPS): %:%.c
#	$(CC) $< $(CFLAGS) -o $@

$(APPS): %:%.o
	$(CC) $(LDFLAGS) $(LIBRARY) -o $@ $<

$(OBJS): %.o:%.c
	$(CC) -c $(CFLAGS) -o $@ $<

.PHONY: all clean
clean:
	-rm -rf $(OBJS) $(APPS)
