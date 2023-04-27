CC = gcc
LD = g++
GDB = cgdb
ECHO = echo
MKDIR = mkdir -p
RM = rm -rf

DIR_BIN = bin
DIR_BUILD = build

DIRS_SRC := source
DIRS_INC := include
DIRS_LIB :=

SRCS_C := main.c
SRCS_C += $(shell find $(DIRS_SRC) -name '*.c')

LIBS_USR :=
LIBS_SYS := m

SRCS := $(SRCS_C)
OBJS := $(SRCS:%.c=$(DIR_BUILD)/%.o)
DEPS := $(OBJS:.o=.d)
LIBS := $(LIBS_USR) $(LIBS_SYS)
APPS := demo

CFLAGS_STD := -std=c99
CFLAGS_DEPS := -MP -MMD
CFLAGS_OPTS := -O0
CFLAGS_DEBUG := -g
CFLAGS_WARNINGS := -Wall
CFLAGS_DSYMS :=
CFLAGS_USYMS :=
CFLAGS_DIRS_INC := $(DIRS_INC:%=-I%)
#CFLAGS_DIRS_INC := $(addprefix -I,$(DIRS_INC))
CFLAGS_DIRS_LIB := $(DIRS_LIB:%=-L%)
#CFLAGS_DIRS_LIB := $(addprefix -L,$(DIRS_LIB))
CFLAGS_LIBS := $(LIBS:%=-l%)
#CFLAGS_LIBS := $(addprefix -l,$(LIBS))
CFLAGS := $(CFLAGS_STD)
CFLAGS += $(CFLAGS_DEPS)
CFLAGS += $(CFLAGS_OPTS)
CFLAGS += $(CFLAGS_DEBUG)
CFLAGS += $(CFLAGS_WARNINGS)
CFLAGS += $(CFLAGS_DSYMS)
CFLAGS += $(CFLAGS_USYMS)
CFLAGS += $(CFLAGS_DIRS_INC)
CFLAGS += $(CFLAGS_LIBS)
#CFLAGS += -Wl,--start-group $(CFLAGS_LIBS) -Wl,--end-group

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

$(APPS): $(OBJS)
	@$(ECHO) "LN: $^ -> $@"
	$(Q) $(LD) $(LDFLAGS) $(CFLAGS) $(LIBRARY) -o $@ $^

$(DIR_BUILD)/%.o: %.c
	$(Q) $(MKDIR) $(@D)
	@$(ECHO) "CC: $< -> $@"
	$(Q) $(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

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
	-$(Q) $(RM) $(DIR_BUILD) $(APPS)
