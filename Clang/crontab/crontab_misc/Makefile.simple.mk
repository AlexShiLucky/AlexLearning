CC = gcc
CFLAGS = -Wall -g
GDB = cgdb
ECHO = echo
RM = rm -rf
SRCS = $(wildcard *.c)
OBJS = $(SRCS %.c=%.o)
APPS = $(SRCS:%.c=%)

# $(info $(OBJS))
# $(info $(APPS))

ifeq ($(V),)
Q := @
else
Q :=
endif

.PHONY: all
all: $(APPS)
	@$(ECHO) [$(APPS)] build complete

#$(APPS): %:%.c
#	$(Q) $(CC) $< $(CFLAGS) -o $@

$(APPS): %:%.o
	@$(ECHO) "LN: $^ -> $@"
	$(Q) $(CC) $(LDFLAGS) $(LIBRARY) -o $@ $<

$(OBJS): %.o:%.c
	@$(ECHO) "CC: $< -> $@"
	$(Q) $(CC) -c $(CFLAGS) -o $@ $<

.PHONY: print-%
print-%: ; @echo $*=$($*)

.PHONY: dbg-%
dbg-%: %
	@$(GDB) $<

.PHONY: run-%
run-%: %
	@./$<

.PHONY: clean
clean:
	-$(Q) $(RM) $(OBJS) $(APPS)
