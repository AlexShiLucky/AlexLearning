APP := demo
################################################################################
# Tools
CC = gcc
LD = g++
AR = ar
GDB = cgdb
ECHO = echo
MKDIR = mkdir -p
RM = rm -rf

################################################################################
DIR_BIN = bin
DIR_BUILD = build

DIRS_SRC :=
DIRS_LIB := $(DIR_BUILD)/lib
DIRS_INC := include

SRCS_C := main.c
ifneq ($(DIRS_SRC),)
SRCS_C += $(shell find $(DIRS_SRC) -name '*.c')
endif

LIBS_NAME_USR := shape
ifneq ($(LIBS_NAME_USR),)
LIBS_USR := $(LIBS_NAME_USR:%=$(DIR_BUILD)/lib/lib%.a)
SRCS_LIB := $(shell find lib/$(basename $@) -name '*.c')
OBJS_LIB := $(SRCS_LIB:%.c=$(DIR_BUILD)/%.o)
DEPS_LIB := $(OBJS_LIB:.o=.d)
DIRS_INC += $(LIBS_NAME_USR:%=lib/lib%/include)
endif
LIBS_NAME_SYS := m

SRCS := $(SRCS_C)
OBJS := $(SRCS:%.c=$(DIR_BUILD)/%.o)
DEPS := $(OBJS:.o=.d)
LIBS_NAME := $(LIBS_NAME_USR) $(LIBS_NAME_SYS)

CFLAGS_STD := -std=c99
CFLAGS_OPTS := -O0
CFLAGS_DEBUG := -g
CFLAGS_WARNINGS := -Wall
CFLAGS_DSYMS :=
CFLAGS_USYMS :=
CFLAGS_DIRS_INC := $(DIRS_INC:%=-I%)
#CFLAGS_DIRS_INC := $(addprefix -I,$(DIRS_INC))
LDFLAGS_DIRS_LIB := $(DIRS_LIB:%=-L %)
#LDFLAGS_DIRS_LIB := $(addprefix -L,$(DIRS_LIB))
LIBS := $(LIBS_NAME:%=-l%)
#LIBS := $(addprefix -l,$(LIBS))
CFLAGS := $(CFLAGS_STD)
CFLAGS += $(CFLAGS_OPTS)
CFLAGS += $(CFLAGS_DEBUG)
CFLAGS += $(CFLAGS_WARNINGS)
CFLAGS += $(CFLAGS_DSYMS)
CFLAGS += $(CFLAGS_USYMS)
CFLAGS += $(CFLAGS_DIRS_INC)

LDFLAGS += $(LDFLAGS_DIRS_LIB)
#CFLAGS += -Wl,--start-group $(CFLAGS_LIBS) -Wl,--end-group

ARFLAGS := -r -c -s

# $(info $(OBJS))
# $(info $(APPS))

ifeq ($(V),)
Q := @
else
Q :=
endif

.PHONY: all
all: $(APP)
	@$(ECHO) [$(APP)] build complete

$(APP): $(OBJS) $(LIBS_USR)
	@$(ECHO) "LN: $^ -> $@"
	$(Q) $(LD) $(LDFLAGS) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

$(DIR_BUILD)/%.o: %.c
	$(Q) $(MKDIR) $(@D)
	@$(ECHO) "CC: $< -> $@"
	$(Q) $(CC) $(CFLAGS) -c $< -o $@

$(DIR_BUILD)/lib/%.a: $(OBJS_LIB)
	@$(MKDIR) $(@D)
	@$(ECHO) "AR: $^ -> $@"
	$(Q) $(AR) $(ARFLAGS) $@ $^

.PHONY: libs
libs: $(LIBS_USR)
	@echo $^

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
