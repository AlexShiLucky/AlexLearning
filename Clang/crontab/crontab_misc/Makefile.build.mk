CC = gcc
CFLAGS = -Wall -g
GDB = cgdb
ECHO = echo
MKDIR = mkdir -p
RM = rm -rf

OUTDIR = build

SRCS = $(wildcard *.c)
OBJS = $(SRCS:%.c=$(OUTDIR)/%.o)
APPS = $(SRCS:%.c=$(OUTDIR)/%)

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

$(OBJS): $(OUTDIR)/%.o:%.c
	$(Q) $(MKDIR) $(OUTDIR)
	@$(ECHO) "CC: $< -> $@"
	$(Q) $(CC) -c $(CFLAGS) -o $@ $<

.PHONY: print-%
print-%: ; @echo $*=$($*)

.PHONY: dbg-%
dbg-%: $(OUTDIR)/%
	@$(GDB) $<

.PHONY: run-%
run-%: $(OUTDIR)/%
	@./$<

.PHONY: clean
clean:
	-$(Q) $(RM) $(OUTDIR)
