# Makefile

INCS = include
SRCS = main.c foo.c bar.c
OBJS = $(SRCS:.c=.o)
APP  = prog

CC = gcc
CFLAGS = -Wall -g
CFLAGS += $(addprefix -I,$(INCS))

#VPATH = src:$(INCS)
vpath %.h $(INCS)
vpath %.c src

all:$(APP)

$(APP):$(OBJS)
	$(CC) $(LDFLAGS) $(LIBRARY) -o $@ $^

%.o:%.c
	$(CC) -c $(CFLAGS) -o $@ $<

.PHONY: all clean
clean:
	-rm -rf $(OBJS) $(APP)
