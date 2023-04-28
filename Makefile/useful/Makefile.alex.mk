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

LIBS_NAME_USR :=
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

################################################################################
CREATE_IFILES := 0
CREATE_SFILES := 0

# $(info $(OBJS))
# $(info $(APPS))

ifeq ($(V),)
Q := @
else
Q :=
endif

################################################################################
# default target
.PHONY: all
all:
	@$(ECHO) build complete

all: build_begin_process libs app build_end_process

################################################################################
# build begin/end process
.PHONY: build_begin_process build_end_process
build_begin_process:
	$(BUILD_BEGIN_PROCESS)

build_end_process:
	$(BUILD_END_PROCESS)

################################################################################
# archive library files
.PHONY: libs
libs: $(LIBS_USR)

$(DIR_BUILD)/lib/%.a: $(OBJS_LIB)
	@$(MKDIR) $(@D)
	@$(ECHO) "AR: $^ -> $@"
	$(Q) $(AR) $(ARFLAGS) $@ $^

################################################################################
# app
.PHONY: app
app: $(APP)

ifeq ($(CREATE_IFILES),1)
app: $(OBJS:%.o=%.i)
endif

ifeq ($(CREATE_SFILES),1)
app: $(OBJS:%.o=%.s)
endif

$(APP): $(OBJS) $(LIBS_USR)
	@$(ECHO) "LN: $^ -> $@"
	$(Q) $(LD) $(LDFLAGS) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

################################################################################
# Pattern rules to build objects
define compile.c2o
$(CC_BEGIN_PROCESS)
@$(ECHO) "CC: $< -> $@"
@$(MKDIR) $(@D)
$(Q) $(CC) -MP -MMD -c $(CPPFLAGS) $(CFLAGS) -o $@ $<
$(CC_END_PROCESS)
endef

define compile.cpp2o
$(CXX_BEGIN_PROCESS)
@$(ECHO) "CXX: $< -> $@"
@$(MKDIR) $(@D)
$(Q) $(CXX) -MP -MMD -c $(CPPFLAGS) $(CXXFLAGS) $(CFLAGS) -o $@ $<
$(CXX_END_PROCESS)
endef

# If assembling with the compiler, ensure "-Wa," is prepended to all APP_ASFLAGS
ifeq ($(AS),$(patsubst %as,%,$(AS)))
COMMA := ,
APP_ASFLAGS :=  $(filter-out $(APP_CFLAGS),$(addprefix -Wa$(COMMA),$(patsubst -Wa$(COMMA)%,%,$(APP_ASFLAGS))))
endif

define compile.s2o
$(AS_BEGIN_PROCESS)
@$(ECHO) "AS: $< -> $@"
@$(MKDIR) $(@D)
$(Q) $(AS) -MP -MMD -c $(CPPFLAGS) $(CFLAGS) $(ASFLAGS) -o $@ $<
$(AS_END_PROCESS)
endef

$(DIR_BUILD)/%.o: %.c
	$(compile.c2o)

$(DIR_BUILD)/%.o: %.cpp
	$(compile.cpp2o)

$(DIR_BUILD)/%.o: %.cc
	$(compile.cpp2o)

$(DIR_BUILD)/%.o: %.cxx
	$(compile.cpp2o)

$(DIR_BUILD)/%.o: %.S
	$(compile.s2o)

$(DIR_BUILD)/%.o: %.s
	$(compile.s2o)

-include $(DEPS)

################################################################################
# Pattern rules to build intermediate files(.s)
define compile.c2s
@$(ECHO) "CPP: $< -> $@"
@$(MKDIR) $(@D)
$(Q) $(CC) -S $(CPPFLAGS) $(CFLAGS) -o $@ $<
endef

define compile.cpp2s
@$(ECHO) "CPP: $< -> $@"
@$(MKDIR) $(@D)
$(Q) $(CXX) -S $(CPPFLAGS) $(CXXFLAGS) $(CFLAGS) -o $@ $<
endef

$(DIR_BUILD)/%.s: %.c
	$(compile.c2s)

$(DIR_BUILD)/%.s: %.cpp
	$(compile.cpp2s)

$(DIR_BUILD)/%.s: %.cc
	$(compile.cpp2s)

$(DIR_BUILD)/%.s: %.cxx
	$(compile.cpp2s)

################################################################################
# Pattern rules to build intermediate files(.i)
define compile.c2i
@$(ECHO) "CPP: $< -> $@"
@$(MKDIR) $(@D)
$(Q) $(CC) -E $(CPPFLAGS) $(CFLAGS) -o $@ $<
endef

define compile.cpp2i
@$(ECHO) "CPP: $< -> $@"
@$(MKDIR) $(@D)
$(Q) $(CXX) -E $(CPPFLAGS) $(CXXFLAGS) $(CFLAGS) -o $@ $<
endef

$(DIR_BUILD)/%.i: %.c
	$(compile.c2i)

$(DIR_BUILD)/%.i: %.cpp
	$(compile.cpp2i)

$(DIR_BUILD)/%.i: %.cc
	$(compile.cpp2i)

$(DIR_BUILD)/%.i: %.cxx
	$(compile.cpp2i)

################################################################################
# Useful Debug Targets
.PHONY: print-%
print-%: ; @echo $*=$($*)

.PHONY: dbg-%
dbg-%: %
	@$(GDB) $<

.PHONY: run-%
run-%: %
	@./$<

################################################################################
# clean target
.PHONY: clean
clean:
	-$(Q) $(RM) $(DIR_BUILD) $(APPS)
