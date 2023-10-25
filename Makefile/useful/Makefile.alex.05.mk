################################################################################
XNAME       := Demo
XELF        := $(XNAME).elf
XBIN        := $(XNAME).bin
XHEX        := $(XNAME).hex
XSREC       := $(XNAME).srec
XMAP        := $(XNAME).map
XASM        := $(XNAME).s
XOBJDUMP    := $(XNAME).objdump

LINKER_SCRIPT   := $(XNAME).ld

XBEGIN      :=
XGENS       := $(XELF)
XEND        :=

################################################################################
ifeq ($(V),)
Q := @
else
Q :=
endif

################################################################################
# Configurable 
CROSS_COMPILE               ?= arm-none-eabi-
CFG_GEN_IFILES              ?= n
CFG_GEN_SFILES              ?= n
CFG_GEN_BIN                 ?= y
CFG_GEN_HEX                 ?= y
CFG_GEN_SREC                ?= y
CFG_GEN_MAP                 ?= y
CFG_GEN_ASM                 ?= n
CFG_GEN_OBJDUMP             ?= y
CFG_OBJDUMP_INCLUDE_SOURCE  ?= y
CFG_OBJDUMP_FULL_CONTENTS   ?= n
CFG_BIN_USE_CP              ?= n

################################################################################
# Defins
DSYMS           :=

USYMS           :=

################################################################################
# Load default variables.
ASFLAGS         :=
CFLAGS          :=
CXXFLAGS        :=
LDFLAGS         :=

# 工程路径
PATH_ROOT       := ..
# 编译路径
PATH_BUILD      := build
# 输出路径
PATH_BIN        := $(PATH_ROOT)/bin

# 库目录
DIRS_LIB        :=
LIBS            :=
DIRS_INC        :=
SRCS_S          :=
SRCS_C          :=
SRCS_CXX        :=

################################################################################
# 工具
AS              :=  $(CROSS_COMPILE)gcc -x assembler-with-cpp
CC              :=  $(CROSS_COMPILE)gcc
CXX             :=  $(CROSS_COMPILE)g++
LD              :=  $(CROSS_COMPILE)gcc
AR              :=  $(CROSS_COMPILE)ar
OC              :=  $(CROSS_COMPILE)objcopy
OD              :=  $(CROSS_COMPILE)objdump
SIZE            :=  $(CROSS_COMPILE)size
NM              :=  $(CROSS_COMPILE)nm
READELF         :=  $(CROSS_COMPILE)readelf
GDB             :=  $(CROSS_COMPILE)gdb
MKDIR           :=  mkdir -p
CP              :=  cp -af
RM              :=  rm -rf
CD              :=  cd
FIND            :=  find
CGDB            :=  cgdb
ECHO            :=  echo

################################################################################
# 头文件目录:从当前目录开始查找,需加上$(PATH_ROOT)/
DIRS_INC += $(PATH_ROOT)/include

################################################################################
# 汇编源文件:从顶层目录下的目录往下列出所有的S文件
SRCS_S +=

################################################################################
# C源文件:从顶层目录下的目录往下列出所有的c文件
SRCS_C += project/main.c

################################################################################
# CPP源文件:从顶层目录下的目录往下列出所有的cpp文件
#SRCS_CXX +=

################################################################################
# 用户库名称
LIBS_NAME_USR :=
ifneq ($(LIBS_NAME_USR),)
LIBS_USR := $(LIBS_NAME_USR:%=$(PATH_BUILD)/lib/lib%.a)
SRCS_LIB := $(shell find lib/$(basename $@) -name '*.c')
OBJS_LIB := $(SRCS_LIB:%.c=$(PATH_BUILD)/%.o)
DEPS_LIB := $(OBJS_LIB:.o=.d)
DIRS_INC += $(LIBS_NAME_USR:%=lib/lib%/include)
endif
# 系统库名称
# 通过以下命令可以找到系统库目录下支持的系统库
# echo 'main(){}'|arm-none-eabi-gcc -E -v -
# echo 'main(){}'|arm-none-eabi-gcc -E -v -march=armv7-m -mcpu=cortex-m3 -mfloat-abi=soft -mthumb -
LIBS_NAME_SYS :=

################################################################################
# 目标文件汇总
OBJS_S  := $(SRCS_S:%.S=$(PATH_BUILD)/%.o)
OBJS_C  := $(SRCS_C:%.c=$(PATH_BUILD)/%.o)
OBJS_CXX:= $(SRCS_CXX:%.cpp=$(PATH_BUILD)/%.o)
OBJS    := $(OBJS_S) $(OBJS_C) $(OBJS_CXX)
# 依赖文件汇总
DEPS    := $(OBJS:%.o=%.d)
# 库汇总
LIBS    += $(LIBS_NAME_USR) $(LIBS_NAME_SYS)

################################################################################
# 编译选项
XFLAGS_STD      := -std=gnu99
XFLAGS_OPT_M    := -march=armv7-m -mcpu=cortex-m3 -mthumb
XFLAGS_OPT_F    :=
XFLAGS_OPT_F    += -fmessage-length=0
XFLAGS_OPT_F    += -fsigned-char
XFLAGS_OPT_F    += -ffunction-sections
XFLAGS_OPT_F    += -fdata-sections
XFLAGS_OPT_F    += -ffreestanding
XFLAGS_OPT_F    += -fno-move-loop-invariants
XFLAGS_OPT_W    :=
XFLAGS_OPT_W    += -Wunused
XFLAGS_OPT_W    += -Wuninitialized
XFLAGS_OPT_W    += -Wall
XFLAGS_OPT_W    += -Wextra
XFLAGS_OPT_O    := -O0
XFLAGS_DEBUG    :=
XFLAGS_DEBUG    += -g0 -ggdb
#XFLAGS_DEBUG    += -g3 -ggdb
XFLAGS_DIRS_INC := $(DIRS_INC:%=-I%)
XFLAGS_DSYMS    := $(DSYMS:%=-D%)
XFLAGS_USYMS    :=

################################################################################
# 追加ASFLAGS参数
ASFLAGS         += -x assembler-with-cpp
ASFLAGS         += $(XFLAGS_OPT_M)
ASFLAGS         += $(XFLAGS_OPT_W)
ASFLAGS         += $(XFLAGS_DIRS_INC)
ASFLAGS         += $(XFLAGS_DSYMS)

################################################################################
# 追加CFLAGS参数
CFLAGS          += $(XFLAGS_STD)
CFLAGS          += $(XFLAGS_OPT_M)
CFLAGS          += $(XFLAGS_OPT_F)
CFLAGS          += $(XFLAGS_OPT_W)
CFLAGS          += $(XFLAGS_OPT_O)
CFLAGS          += $(XFLAGS_DEBUG)
CFLAGS          += $(XFLAGS_DIRS_INC)
CFLAGS          += $(XFLAGS_DSYMS)
CFLAGS          += $(XFLAGS_USYMS)

################################################################################
# 追加LDFLAGS参数
LDFLAGS         += -nostartfiles
# 交叉工具链库目录下包含nano.specs和nosys.specs文件
LDFLAGS         += --specs=nano.specs --specs=nosys.specs
LDFLAGS         += -Wl,-gc-sections
ifneq ($(LINKER_SCRIPT),)
LDFLAGS         += -T'$(LINKER_SCRIPT)'
endif

ifneq ($(LIBS),)
LDFLAGS_LIBS    := $(LIBS:%=-l%)
endif
ifneq ($(DIRS_LIB),)
LDFLAGS_DIRS_LIB:= $(DIRS_LIB:%=-L %)
endif

LDFLAGS         += -Wl,--start-group $(LDFLAGS_LIBS) -Wl,--end-group
LDFLAGS         += $(LDFLAGS_DIRS_LIB)

ifeq ($(CFG_GEN_MAP),y)
LDFLAGS         += -Wl,-Map=$(XMAP)
endif

################################################################################
# 其他选项
ARFLAGS         := -r -c -s
GENDEPS         := -MP -MMD

#OBJDUMP_FLAGS  := --disassemble --syms --all-header
OBJDUMP_FLAGS   := -d -t -x
ifeq ($(CFG_OBJDUMP_INCLUDE_SOURCE),y)
OBJDUMP_FLAGS   += --source
endif
ifeq ($(CFG_OBJDUMP_FULL_CONTENTS),y)
OBJDUMP_FLAGS   += --full-contents
endif

ASM_FLAGS       := -d -t

################################################################################
# 函数
BASENAME = $(basename $<)
DATENAME = $(basename $@)_$(shell date +%Y%m%d)$(suffix $@)
#DATENAME = $(basename $@)_$(shell date +%Y%m%d_%H%M%S)$(suffix $@)


################################################################################
ifeq ($(CFG_GEN_BIN),y)
XGENS += $(XBIN)
endif

ifeq ($(CFG_GEN_HEX),y)
XGENS += $(XHEX)
endif

ifeq ($(CFG_GEN_SREC),y)
XGENS += $(XSREC)
endif

ifeq ($(CFG_GEN_ASM),y)
XGENS += $(XASM)
endif

ifeq ($(CFG_GEN_OBJDUMP),y)
XGENS += $(XOBJDUMP)
endif

################################################################################
.PHONY: all
all: $(XBEGIN) $(XGENS) $(XEND)
	@$(ECHO) [$(XELF)] build complete

$(XELF): $(OBJS) $(LIBS_USR)
	@$(ECHO) "[LN] $@"
	$(Q) $(LD) $(LDFLAGS) $(CFLAGS) -o $@ $(OBJS) $(LIBS_USR)
ifeq ($(CFG_GEN_MAP),y)
	@$(ECHO)    | tee -a $(XMAP)
	@$(SIZE) $@ | tee -a $(XMAP)
	@$(ECHO)    | tee -a $(XMAP)
endif

$(XBIN): $(XELF)
	@$(ECHO) "[GEN] $@"
ifeq ($(CFG_BIN_USE_CP),y)
	$(Q) $(OC) -O binary $< $@
	@$(CP) $@ $(PATH_BIN)/$(DATENAME)
else
	$(Q) $(OC) -O binary $< $(PATH_BIN)/$(DATENAME)
endif

$(XHEX): $(XELF)
	@$(ECHO) "[GEN] $@"
ifeq ($(CFG_BIN_USE_CP),y)
	$(Q) $(OC) -O ihex $< $@
	@$(CP) $@ $(PATH_BIN)/$(DATENAME)
else
	$(Q) $(OC) -O ihex $< $(PATH_BIN)/$(DATENAME)
endif

$(XSREC): $(XELF)
	@$(ECHO) "[GEN] $@"
ifeq ($(CFG_BIN_USE_CP),y)
	$(Q) $(OC) -O srec $< $@
	@$(CP) $@ $(PATH_BIN)/$(DATENAME)
else
	$(Q) $(OC) -O srec $< $(PATH_BIN)/$(DATENAME)
endif

$(XASM): $(XELF)
	@$(ECHO) "[GEN] $@"
	$(Q) $(OD) $(ASM_FLAGS) $< >$@

$(XOBJDUMP): $(XELF)
	@$(ECHO) "[GEN] $@"
	$(Q) $(OD) $(OBJDUMP_FLAGS) $< >$@

$(PATH_BUILD)/%.o: $(PATH_ROOT)/%.c
	@$(MKDIR) $(@D)
ifeq ($(CFG_GEN_IFILES),y)
	@$(ECHO) "[CC -E] $(<:.c=.i)"
	$(Q) $(CC) -E -C $(CFLAGS) -o $(@:.o=.i) $<
endif
ifeq ($(CFG_GEN_SFILES),y)
	@$(ECHO) "[CC -S] $(<:.c=.s)"
	$(Q) $(CC) -S $(CFLAGS) -o $(@:.o=.s) $<
endif
	@$(ECHO) "[CC] $@"
	$(Q) $(CC) $(GENDEPS) -c $(CFLAGS) $($(BASENAME)_FLAGS) -o $@ $<
	$(CC_POST_PROCESS)

$(PATH_BUILD)/%.o: $(PATH_ROOT)/%.S
	@$(ECHO) "[AS] $@"
	@$(MKDIR) $(@D)
	$(Q) $(AS) $(GENDEPS) -c $(ASFLAGS) $($(BASENAME)_FLAGS) -o $@ $<
	$(AS_POST_PROCESS)

$(PATH_BUILD)/lib/%.a: $(OBJS_LIB)
	@$(ECHO) "AR: $^ -> $@"
	$(Q) $(AR) $(ARFLAGS) $@ $^

################################################################################
.PHONY: libs
libs: $(LIBS_USR)
	@echo $^

-include $(DEPS)

################################################################################
# 有用的调试目标
.PHONY: print-%
print-%: ; @echo $*=$($*)

.PHONY: dbg-%
dbg-%: %
	@$(CGDB) -d $(GDB) $<

.PHONY: run-%
run-%: %
	@./$< > run.log

.PHONY: clean distclean
clean:
	-$(Q) $(RM) $(PATH_BUILD) $(XELF)

distclean: clean
	-$(Q) $(RM) $(XGENS)
