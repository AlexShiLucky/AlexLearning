TOPDIR := $(shell pwd | sed -e 's/ /\\ /g')
#-------------------------------------------------------------------------------
#              变量初始定义,由包含的 MAKEFILE片段追加值
#-------------------------------------------------------------------------------

# -I编译器选项的包含目录列表(在使用时添加-I前缀)
# 包含Lib库头文件路径
DIRS_HEADER :=

# -L链接器选项的库目录列表(使用时添加-L前缀)
# 包含Lib库路径
DIRS_LIBRARY :=

# -l链接器选项的库名称列表(使用时添加-l前缀)
# 包含Lib库名称
LIBS_NAME :=

# List of library names for -msys-lib linker option (-msys-lib added when used).
# These are libraries that might be located in the BSP and depend on the BSP
# library, or vice versa
ALT_BSP_DEP_LIBRARY_NAMES :=

# 链接器的依赖项列表。 通常是每个库(*.a)文件的完整路径名。
# Includes the BSP.
DEPS_LD :=

# 支持运行make来构建它们的根库目录列表。
DIRS_MAKEABLE_LIBRARY :=

# 针对不同类型的输入文件传递给编译器的通用标志。
CFLAGS_GENERIC :=
CXXFLAGS_GENERIC :=
CPPFLAGS_GENERIC :=
ASFLAGS_GENERIC :=
LDFLAGS_GENERIC :=

# 控制构建详细程度
#
#  V=1,2: 启用命令回显
#  V=2:   在工具和脚本中启用错误/详细选项

ifeq ($(V),1)
export Q :=
else
ifeq ($(V),2)
export Q :=
else
export Q := @
endif
endif

#-------------------------------------------------------------------------------
#                         调整路径宏
#
# 如果定义了COMSPEC/ComSpec，Make是通过 Cygwin从Windows启动的。
# 调整路径宏adjust-path-to-unix将绝对的windows路径转换为unix样式路径(示例：c:/dir -> /c/dir)
# 这将保证路径能被GNU Make识别。
# 如果没有定义COMSPEC/ComSpec，就认为Make是从linux启动的，不需要调整。
#
#-------------------------------------------------------------------------------

ifndef COMSPEC
ifdef ComSpec
COMSPEC = $(ComSpec)
endif # ComSpec
endif # COMSPEC

ifdef COMSPEC # if Windows OS

ifeq ($(MAKE_VERSION),3.81)
#
# adjust-path-to-unix/adjust-path-to-windows for Mingw Gnu Make on Windows
#
# Example Usage:
# $(call adjust-path-to-unix,c:/aaa/bbb) => /c/aaa/bbb
# $(call adjust-path-to-windows,/c/aaa/bbb) => c:/aaa/bbb
# $(call adjust-path-to-windows,/cygdrive/c/aaa/bbb) => c:/aaa/bbb
#

#
# adjust-path-to-unix
#  - 将反斜杠字符转换为正斜杠
#  - 如果输入参数($1)是空字符串，则返回空字符串
#  - 如果输入参数($1)不包含字符串":/"，则返回输入参数
#  - 使用sed命令，将windows路径[c:/...]转换为mingw路径[/c/...]
define adjust-path-to-unix
$(strip \
$(if $1,\
$(if $(findstring :/,$(subst \,/,$1)),\
$(shell echo $(subst \,/,$1) | sed -e 's,^\([a-zA-Z]\):/,/\1/,'),\
$(subst \,/,$1))))
endef

#
# adjust-path-to-windows
#  - 将反斜杠字符转换为正斜杠
#  - 如果输入参数($1)是空字符串，则返回空字符串
#  - 如果输入参数($1)不以正斜杠'/'字符开头，则返回输入参数
#  - 使用sed命令，将mingw路径[/c/...]或cygwin路径[/c/cygdrive/...]转换为windows路径 [c:/...]
define adjust-path-to-windows
$(strip \
$(if $1,\
$(if $(findstring $(subst \,/,$1),$(patsubst /%,%,$(subst \,/,$1))),\
$(subst \,/,$1),\
$(shell echo $(subst \,/,$1) | sed -e 's,^/cygdrive/\([a-zA-Z]\)/,\1:/,' -e 's,^/\([a-zA-Z]\)/,\1:/,'))))
endef

else # MAKE_VERSION != 3.81 (MAKE_VERSION == 3.80 or MAKE_VERSION == 3.79)
#
#  adjust-path-to-unix for Cygwin Gnu Make
# $(call adjust-path-to-unix,c:/aaa/bbb) = /cygdrive/c/aaa/bbb
# $(call adjust-path-to-windows,/cygdrive/c/aaa/bbb) = c:/aaa/bbb
#
adjust-path-to-unix = $(if $1,$(shell cygpath -u "$1"),)
adjust-path-to-windows = $(if $1,$(shell cygpath -m "$1"),)
endif

else # !COMSPEC

adjust-path-to-unix = $1
adjust-path-to-windows = $1

endif # COMSPEC


#vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
#                             编译配置导入开始                                 v
#vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
#START GENERATED
# BUILD_CONFIGS += default
# BUILD_CONFIGS += Alpha
# BUILD_CONFIGS += Beta
# BUILD_CONFIGS += Debug
# BUILD_CONFIGS += Preview
# BUILD_CONFIGS += Release
# 
ACTIVE_BUILD_CONFIG := default
include $(ACTIVE_BUILD_CONFIG)_config.mk
#END GENERATED
#^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
#                             编译配置导入结束                                 ^
#^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


#-------------------------------------------------------------------------------
#                                默认目标
#-------------------------------------------------------------------------------

# 如果尚未定义，则定义用于回显输出的变量。
ifeq ($(ECHO),)
ECHO := echo
endif

# 将"all"目标规则放在包含的makefile片段之前，因为它们可能定义规则
# 我们不希望其中之一成为默认规则。
.PHONY: all
all:
	@$(ECHO) [$(APP_NAME) build complete]

all: begin_process libs app end_process


#-------------------------------------------------------------------------------
#                 			取决于生成内容的变量
#-------------------------------------------------------------------------------

# 为每个构建配置定义目标文件目录
DIR_OUTPUT := $(OBJ_ROOT_DIR)/$(ACTIVE_BUILD_CONFIG)

# ifeq ($(LIB_ROOT_DIR),)
# $(error Edit Makefile and provide a value for LIB_ROOT_DIR)
# endif
# 
# ifeq ($(wildcard $(LIB_ROOT_DIR)),)
# $(error LIB directory does not exist: $(LIB_ROOT_DIR))
# endif
# 
# # 定义LIB根目录的绝对路径
# ABS_LIB_ROOT_DIR := $(call adjust-path-to-windows,$(shell cd "$(LIB_ROOT_DIR)"; pwd))
# 
# # 包括makefile片段。
# # 在包含每个makefile片段之前定义变量 ALT_LIBRARY_ROOT_DIR，以便它知道自身的路径。
# BSP_INCLUDE_FILE := $(LIB_ROOT_DIR)/public.mk
# ALT_LIBRARY_ROOT_DIR := $(LIB_ROOT_DIR)
# include $(BSP_INCLUDE_FILE)


# ifneq ($(WARNING.SMALL_STACK_SIZE),)
# # This WARNING is here to protect you from unknowingly using a very small stack
# # If the warning is set, increase your stack size or enable the BSP small stack
# # setting to eliminate the warning
# $(warning WARNING: $(WARNING.SMALL_STACK_SIZE))
# endif

# # If the BSP public.mk indicates that ALT_SIM_OPTIMIZE is set, rename the ELF
# # by prefixing it with RUN_ON_HDL_SIMULATOR_ONLY_.
# ifneq ($(filter -DALT_SIM_OPTIMIZE,$(CPPFLAGS_GENERIC)),)
# ELF := RUN_ON_HDL_SIMULATOR_ONLY_$(ELF)
# endif

# # If the BSP public.mk indicates that ALT_PROVIDE_GMON is set, add option to
# # download_elf target
# ifneq ($(filter -DALT_PROVIDE_GMON,$(CPPFLAGS_GENERIC)),)
# GMON_OUT_FILENAME := gmon.out
# WRITE_GMON_OPTION := --write-gmon $(GMON_OUT_FILENAME)
# endif

# Name of ELF application.
APP_NAME := $(basename $(ELF))

# # Set to defaults if variables not already defined in settings.
# ifeq ($(LINKER_SCRIPT),)
# LINKER_SCRIPT := $(BSP_LINKER_SCRIPT)
# endif
# ifeq ($(CRT0),)
# CRT0 := $(BSP_CRT0)
# endif
# ifeq ($(SYS_LIB),)
# SYS_LIB := $(BSP_SYS_LIB)
# endif

OBJDUMP_NAME := $(APP_NAME).objdump
#OBJDUMP_FLAGS := --disassemble --syms --all-header
OBJDUMP_FLAGS := -d -t -x
ifeq ($(OBJDUMP_INCLUDE_SOURCE),1)
OBJDUMP_FLAGS += --source
endif
ifeq ($(OBJDUMP_FULL_CONTENTS),1)
OBJDUMP_FLAGS += --full-contents
endif

ASM_NAME := $(APP_NAME).s.gnu
ASM_FLAGS := -d -t

# 创建链接器依赖项列表(*.a文件).
APP_LDDEPS := $(DEPS_LD) $(LDDEPS)

# 获取列表并添加所需的前缀
APP_INC_DIRS := $(addprefix -I, $(DIRS_HEADER) $(APP_INCLUDE_DIRS) $(INC_DIRS))
ASM_INC_PREFIX := -Wa,-I
APP_ASM_INC_DIRS := $(addprefix $(ASM_INC_PREFIX), $(DIRS_HEADER) $(APP_INCLUDE_DIRS) $(INC_DIRS))
APP_LIB_DIRS := $(addprefix -L, $(DIRS_LIBRARY) $(APP_LIBRARY_DIRS) $(LIB_DIRS))
APP_LIBS := $(addprefix -l, $(LIBS_NAME) $(APP_LIBRARY_NAMES) $(LIBS))

# ifneq ($(AVOID_NIOS2_GCC3_OPTIONS),)
# 
# #
# # Avoid Nios II GCC 3.X options.
# #
# 
# # Detect if small newlib C library is requested.
# # If yes, remove the -msmallc option because it is
# # now handled by other means.
# ifneq ($(filter -msmallc,$(LDFLAGS_GENERIC)),)
# 	LDFLAGS_GENERIC := $(filter-out -msmallc,$(LDFLAGS_GENERIC))
# 	ALT_C_LIBRARY := smallc
# else
# 	ALT_C_LIBRARY := c
# endif
# 
# # Put each BSP dependent library in a group to avoid circular dependencies.
# APP_BSP_DEP_LIBS := $(foreach l,$(ALT_BSP_DEP_LIBRARY_NAMES),-Wl,--start-group -l$(ALT_C_LIBRARY) -lgcc -lm -l$(l) -Wl,--end-group)
# 
# else # !AVOID_NIOS2_GCC3_OPTIONS
# 
# #
# # Use Nios II GCC 3.X options.
# #
# ALT_BSP_DEP_LIBRARY_NAMES += $(ALT_BSP_DEP_LIBRARY_NAMES) m
# APP_BSP_DEP_LIBS := $(addprefix -msys-lib=, $(ALT_BSP_DEP_LIBRARY_NAMES))
# 
# endif # !AVOID_NIOS2_GCC3_OPTIONS

# C预处理器、C/C++编译器、汇编器和链接器的参数
APP_CFLAGS := $(APP_CFLAGS_DEFINED_SYMBOLS) \
              $(APP_CFLAGS_UNDEFINED_SYMBOLS) \
              $(APP_CFLAGS_OPTIMIZATION) \
              $(APP_CFLAGS_DEBUG_LEVEL) \
              $(APP_CFLAGS_WARNINGS) \
              $(APP_CFLAGS_USER_FLAGS) \
              $(CFLAGS_GENERIC) \
              $(CFLAGS)

# 仅适用于C++编译器的参数。
APP_CXXFLAGS := $(CXXFLAGS_GENERIC) $(CXXFLAGS)

# 仅用于C预处理器的参数。
# 为每个包含目录加上-I前缀。
APP_CPPFLAGS := $(APP_INC_DIRS) \
                $(CPPFLAGS_GENERIC) \
                $(CPPFLAGS)

# 仅用于汇编程序的参数。
APP_ASFLAGS := $(APP_ASM_INC_DIRS) \
               $(ASFLAGS_GENERIC) \
               $(APP_ASFLAGS_USER) \
               $(ASFLAGS)

# 仅用于链接器的参数。
APP_LDFLAGS := $(APP_LDFLAGS_USER)

ifneq ($(LINKER_SCRIPT),)
APP_LDFLAGS += -T'$(LINKER_SCRIPT)'
endif

ifneq ($(AVOID_NIOS2_GCC3_OPTIONS),)

# Avoid Nios II GCC 3.x options.
ifneq ($(CRT0),)
APP_LDFLAGS += $(CRT0)
endif

# The equivalent of the -msys-lib option is provided
# by the GROUP() command in the linker script.
# Note this means the SYS_LIB variable is now ignored.

else # !AVOID_NIOS2_GCC3_OPTIONS

# Use Nios II GCC 3.x options.
ifneq ($(CRT0),)
APP_LDFLAGS += -msys-crt0='$(CRT0)'
endif
ifneq ($(SYS_LIB),)
APP_LDFLAGS += -msys-lib=$(SYS_LIB)
endif

endif # !AVOID_NIOS2_GCC3_OPTIONS

APP_LDFLAGS += \
           $(APP_LIB_DIRS) \
           $(LDFLAGS_GENERIC) \
           $(LDFLAGS)

# 链接输出的map文件名称
LINKER_MAP_NAME := $(APP_NAME).map
# 需要输出map文件则添加输出map文件的链接器选项
ifeq ($(CREATE_LINKER_MAP), 1)
APP_LDFLAGS += -Wl,-Map=$(LINKER_MAP_NAME)
endif

# # QUARTUS_PROJECT_DIR and SOPC_NAME need to be defined if you want the
# # mem_init_install target of the mem_init.mk (located in the associated BSP)
# # to know how to copy memory initialization files (e.g. .dat, .hex) into
# # directories required for Quartus compilation or RTL simulation.
# 
# # Defining QUARTUS_PROJECT_DIR causes mem_init_install to copy memory
# # initialization files into your Quartus project directory. This is required
# # to provide the initial memory contents of FPGA memories that can be
# # initialized by the programming file (.sof) or Hardcopy ROMs. It is also used
# # for VHDL simulation of on-chip memories.
# 
# # Defining SOPC_NAME causes the mem_init_install target to copy memory
# # initialization files into your RTL simulation directory.  This is required
# # to provide the initial memory contents of all memories that can be
# # initialized by RTL simulation. This variable should be set to the same name
# # as your SOPC Builder system name. For example, if you have a system called
# # "foo.sopc", this variable should be set to "foo".
# 
# # If SOPC_NAME is not set and QUARTUS_PROJECT_DIR is set, then derive SOPC_NAME.
# ifeq ($(SOPC_NAME),)
# ifneq ($(QUARTUS_PROJECT_DIR),)
# SOPC_NAME := $(basename $(notdir $(wildcard $(QUARTUS_PROJECT_DIR)/*.sopcinfo)))
# endif
# endif

# # Defining JDI_FILE is required to specify the JTAG Debug Information File
# # path. This file is generated by Quartus, and is needed along with the
# # .sopcinfo file to resolve processor instance ID's from names in a multi-CPU
# # systems. For multi-CPU systems, the processor instance ID is used to select
# # from multiple CPU's during ELF download.
# 
# # Both JDI_FILE and SOPCINFO_FILE are provided by the BSP if they found during
# # BSP creation. If JDI_FILE is not set and QUARTUS_PROJECT_DIR is set, then
# # derive JDI_FILE. We do not attempt to derive SOPCINFO_FILE since there may be
# # multiple .sopcinfo files in a Quartus project.
# ifeq ($(JDI_FILE),)
# ifneq ($(QUARTUS_PROJECT_DIR),)
# JDI_FILE := $(firstword $(wildcard $(QUARTUS_PROJECT_DIR)/output_files/*.jdi) $(wildcard $(QUARTUS_PROJECT_DIR)/*.jdi))
# endif
# endif

# # 用于 hdl 模拟的运行时根目录的路径
# RUNTIME_ROOT_DIR := $(DIR_OUTPUT)/runtime



#-------------------------------------------------------------------------------
#           MAKEFILE INCLUDES DEPENDENT ON GENERATED CONTENT
#-------------------------------------------------------------------------------
# mem_init.mk is a generated makefile fragment. This file defines all targets
# used to generate HDL initialization simulation files and pre-initialized
# onchip memory files.
# MEM_INIT_FILE :=  $(LIB_ROOT_DIR)/mem_init.mk
# include $(MEM_INIT_FILE)

# Create list of object files to be built using the list of source files.
# The source file hierarchy is preserved in the object tree.
# The supported file extensions are:
#
# .c            - for C files
# .cxx .cc .cpp - for C++ files
# .S .s         - for assembler files
#
# Handle source files specified by --src-dir & --src-rdir differently, to
# save some processing time in calling the adjust-path-to-unix macro.

OBJ_LIST_C 		:= $(patsubst %.c,%.o,$(filter %.c,$(C_SRCS)))
OBJ_LIST_CPP	:= $(patsubst %.cpp,%.o,$(filter %.cpp,$(CXX_SRCS)))
OBJ_LIST_CXX 	:= $(patsubst %.cxx,%.o,$(filter %.cxx,$(CXX_SRCS)))
OBJ_LIST_CC 	:= $(patsubst %.cc,%.o,$(filter %.cc,$(CXX_SRCS)))
OBJ_LIST_S 		:= $(patsubst %.S,%.o,$(filter %.S,$(ASM_SRCS)))
OBJ_LIST_SS		:= $(patsubst %.s,%.o,$(filter %.s,$(ASM_SRCS)))

OBJ_LIST := $(sort $(OBJ_LIST_C) $(OBJ_LIST_CPP) $(OBJ_LIST_CXX) \
				$(OBJ_LIST_CC) $(OBJ_LIST_S) $(OBJ_LIST_SS))

SDIR_OBJ_LIST_C		:= $(patsubst %.c,%.o,$(filter %.c,$(SDIR_C_SRCS)))
SDIR_OBJ_LIST_CPP	:= $(patsubst %.cpp,%.o,$(filter %.cpp,$(SDIR_CXX_SRCS)))
SDIR_OBJ_LIST_CXX 	:= $(patsubst %.cxx,%.o,$(filter %.cxx,$(SDIR_CXX_SRCS)))
SDIR_OBJ_LIST_CC 	:= $(patsubst %.cc,%.o,$(filter %.cc,$(SDIR_CXX_SRCS)))
SDIR_OBJ_LIST_S		:= $(patsubst %.S,%.o,$(filter %.S,$(SDIR_ASM_SRCS)))
SDIR_OBJ_LIST_SS	:= $(patsubst %.s,%.o,$(filter %.s,$(SDIR_ASM_SRCS)))

SDIR_OBJ_LIST := $(sort $(SDIR_OBJ_LIST_C) $(SDIR_OBJ_LIST_CPP) \
				$(SDIR_OBJ_LIST_CXX) $(SDIR_OBJ_LIST_CC) $(SDIR_OBJ_LIST_S) \
				$(SDIR_OBJ_LIST_SS))

# Relative-pathed objects that being with "../" are handled differently.
#
# Regular objects are created as
#   $(DIR_OUTPUT)/<path>/<filename>.o
# where the path structure is maintained under the obj directory.  This
# applies for both absolute and relative paths; in the absolute path
# case this means the entire source path will be recreated under the obj
# directory.  This is done to allow two source files with the same name
# to be included as part of the project.
#
# Note: On Cygwin, the path recreated under the obj directory will be
# the cygpath -u output path.
#
# Relative-path objects that begin with "../" cause problems under this
# scheme, as $(DIR_OUTPUT)/../<rest of path>/ can potentially put the object
# files anywhere in the system, creating clutter and polluting the source tree.
# As such, their paths are flattened - the object file created will be
# $(DIR_OUTPUT)/<filename>.o.  Due to this, two files specified with
# "../" in the beginning cannot have the same name in the project.  VPATH
# will be set for these sources to allow make to relocate the source file
# via %.o rules.
#
# The following lines separate the object list into the flatten and regular
# lists, and then handles them as appropriate.

FLATTEN_OBJ_LIST := $(filter ../%,$(OBJ_LIST))
FLATTEN_APP_OBJS := $(addprefix $(DIR_OUTPUT)/,$(notdir $(FLATTEN_OBJ_LIST)))

REGULAR_OBJ_LIST 		:= $(filter-out $(FLATTEN_OBJ_LIST),$(OBJ_LIST))
REGULAR_OBJ_LIST_C 		:= $(filter $(OBJ_LIST_C),$(REGULAR_OBJ_LIST))
REGULAR_OBJ_LIST_CPP	:= $(filter $(OBJ_LIST_CPP),$(REGULAR_OBJ_LIST))
REGULAR_OBJ_LIST_CXX 	:= $(filter $(OBJ_LIST_CXX),$(REGULAR_OBJ_LIST))
REGULAR_OBJ_LIST_CC 	:= $(filter $(OBJ_LIST_CC),$(REGULAR_OBJ_LIST))
REGULAR_OBJ_LIST_S 		:= $(filter $(OBJ_LIST_S),$(REGULAR_OBJ_LIST))
REGULAR_OBJ_LIST_SS		:= $(filter $(OBJ_LIST_SS),$(REGULAR_OBJ_LIST))

FLATTEN_SDIR_OBJ_LIST := $(filter ../%,$(SDIR_OBJ_LIST))
FLATTEN_SDIR_APP_OBJS := $(addprefix $(DIR_OUTPUT)/,$(notdir $(FLATTEN_SDIR_OBJ_LIST)))

REGULAR_SDIR_OBJ_LIST 		:= $(filter-out $(FLATTEN_SDIR_OBJ_LIST),$(SDIR_OBJ_LIST))
REGULAR_SDIR_OBJ_LIST_C 	:= $(filter $(SDIR_OBJ_LIST_C),$(REGULAR_SDIR_OBJ_LIST))
REGULAR_SDIR_OBJ_LIST_CPP	:= $(filter $(SDIR_OBJ_LIST_CPP),$(REGULAR_SDIR_OBJ_LIST))
REGULAR_SDIR_OBJ_LIST_CXX 	:= $(filter $(SDIR_OBJ_LIST_CXX),$(REGULAR_SDIR_OBJ_LIST))
REGULAR_SDIR_OBJ_LIST_CC 	:= $(filter $(SDIR_OBJ_LIST_CC),$(REGULAR_SDIR_OBJ_LIST))
REGULAR_SDIR_OBJ_LIST_S 	:= $(filter $(SDIR_OBJ_LIST_S),$(REGULAR_SDIR_OBJ_LIST))
REGULAR_SDIR_OBJ_LIST_SS	:= $(filter $(SDIR_OBJ_LIST_SS),$(REGULAR_SDIR_OBJ_LIST))

VPATH := $(sort $(dir $(FLATTEN_OBJ_LIST)) $(dir $(FLATTEN_SDIR_OBJ_LIST)))

APP_OBJS_C := $(addprefix $(DIR_OUTPUT)/,\
	$(REGULAR_SDIR_OBJ_LIST_C) \
	$(foreach s,$(REGULAR_OBJ_LIST_C),$(call adjust-path-to-unix,$s)))

APP_OBJS_CPP := $(addprefix $(DIR_OUTPUT)/,\
	$(REGULAR_SDIR_OBJ_LIST_CPP) \
	$(foreach s,$(REGULAR_OBJ_LIST_CPP),$(call adjust-path-to-unix,$s)))

APP_OBJS_CXX := $(addprefix $(DIR_OUTPUT)/,\
	$(REGULAR_SDIR_OBJ_LIST_CXX) \
	$(foreach s,$(REGULAR_OBJ_LIST_CXX),$(call adjust-path-to-unix,$s)))

APP_OBJS_CC := $(addprefix $(DIR_OUTPUT)/,\
	$(REGULAR_SDIR_OBJ_LIST_CC) \
	$(foreach s,$(REGULAR_OBJ_LIST_CC),$(call adjust-path-to-unix,$s)))

APP_OBJS_S := $(addprefix $(DIR_OUTPUT)/,\
	$(REGULAR_SDIR_OBJ_LIST_S) \
	$(foreach s,$(REGULAR_OBJ_LIST_S),$(call adjust-path-to-unix,$s)))

APP_OBJS_SS := $(addprefix $(DIR_OUTPUT)/,\
	$(REGULAR_SDIR_OBJ_LIST_SS) \
	$(foreach s,$(REGULAR_OBJ_LIST_SS),$(call adjust-path-to-unix,$s)))

APP_OBJS := $(APP_OBJS_C) $(APP_OBJS_CPP) $(APP_OBJS_CXX) $(APP_OBJS_CC) \
	$(APP_OBJS_S) $(APP_OBJS_SS) \
	$(FLATTEN_APP_OBJS) $(FLATTEN_SDIR_APP_OBJS)

# Add any extra user-provided object files.
APP_OBJS += $(OBJS)

# Create list of dependancy files for each object file.
APP_DEPS := $(APP_OBJS:.o=.d)

# Patch the Elf file with system specific information

# # Patch the Elf with the name of the sopc system
# ifneq ($(SOPC_NAME),)
# ELF_PATCH_FLAG += --sopc_system_name $(SOPC_NAME)
# endif
# 
# # Patch the Elf with the absolute path to the Quartus Project Directory
# ifneq ($(QUARTUS_PROJECT_DIR),)
# ABS_QUARTUS_PROJECT_DIR := $(call adjust-path-to-windows,$(shell cd "$(QUARTUS_PROJECT_DIR)"; pwd))
# ELF_PATCH_FLAG += --quartus_project_dir "$(ABS_QUARTUS_PROJECT_DIR)"
# endif
# 
# # Patch the Elf and download args with the JDI_FILE if specified
# ifneq ($(wildcard $(JDI_FILE)),)
# ELF_PATCH_FLAG += --jdi $(JDI_FILE)
# DOWNLOAD_JDI_FLAG := --jdi $(JDI_FILE)
# endif
# 
# # Patch the Elf with the SOPCINFO_FILE if specified
# ifneq ($(wildcard $(SOPCINFO_FILE)),)
# ELF_PATCH_FLAG += --sopcinfo $(SOPCINFO_FILE)
# endif
# 
# # Use the DOWNLOAD_CABLE variable to specify which JTAG cable to use.
# # This is not needed if you only have one cable.
# ifneq ($(DOWNLOAD_CABLE),)
# DOWNLOAD_CABLE_FLAG := --cable '$(DOWNLOAD_CABLE)'
# endif


#-------------------------------------------------------------------------------
#                           	构建前/后处理过程
#-------------------------------------------------------------------------------
begin_process :
	$(BUILD_BEGIN_PROCESS)

end_process :
	$(BUILD_END_PROCESS)

.PHONY: begin_process end_process


#-------------------------------------------------------------------------------
#                                 	工具链
#-------------------------------------------------------------------------------

#
# 如果尚未定义，请设置工具默认变量。 
# 如果定义了这些，它们通常会在包含的makefile片段中定义。
#
ifeq ($(DEFAULT_CROSS_COMPILE),)
DEFAULT_CROSS_COMPILE :=
endif

ifeq ($(DEFAULT_STACKREPORT),)
DEFAULT_STACKREPORT :=
endif

ifeq ($(DEFAULT_DOWNLOAD),)
DEFAULT_DOWNLOAD :=
endif

ifeq ($(DEFAULT_FLASHPROG),)
DEFAULT_FLASHPROG :=
endif

ifeq ($(DEFAULT_ELFPATCH),)
DEFAULT_ELFPATCH :=
endif

ifeq ($(DEFAULT_RM),)
DEFAULT_RM := rm -f
endif

ifeq ($(DEFAULT_CP),)
DEFAULT_CP := cp -f
endif

ifeq ($(DEFAULT_MKDIR),)
DEFAULT_MKDIR := mkdir -p
endif

#
# 如果尚未定义，则将工具变量设置为默认值。
# 如果定义了这些，则它们通常由该生成文件的生成部分中的设置定义。
#
ifeq ($(CROSS_COMPILE),)
CROSS_COMPILE := $(DEFAULT_CROSS_COMPILE)
endif

ifeq ($(origin CC),default)
CC := $(CROSS_COMPILE)gcc -xc
endif

ifeq ($(origin CXX),default)
CXX := $(CROSS_COMPILE)gcc -xc++
endif

ifeq ($(origin AS),default)
AS := $(CROSS_COMPILE)gcc
endif

ifeq ($(origin AR),default)
AR := $(CROSS_COMPILE)ar
endif

ifeq ($(origin LD),default)
LD := $(CROSS_COMPILE)g++
endif

ifeq ($(origin RM),default)
RM := $(DEFAULT_RM)
endif

ifeq ($(NM),)
NM := $(CROSS_COMPILE)nm
endif

ifeq ($(SIZE),)
SIZE := $(CROSS_COMPILE)size
endif

ifeq ($(CP),)
CP := $(DEFAULT_CP)
endif

ifeq ($(OBJDUMP),)
OBJDUMP := $(CROSS_COMPILE)objdump
endif

ifeq ($(OBJCOPY),)
OBJCOPY := $(CROSS_COMPILE)objcopy
endif

# ifeq ($(STACKREPORT),)
# STACKREPORT := $(DEFAULT_STACKREPORT) --prefix $(CROSS_COMPILE)
# else
# DISABLE_STACKREPORT := 1
# endif

ifeq ($(DOWNLOAD),)
DOWNLOAD := $(DEFAULT_DOWNLOAD)
endif

ifeq ($(FLASHPROG),)
FLASHPROG := $(DEFAULT_FLASHPROG)
endif

ifeq ($(ELFPATCH),)
ELFPATCH := $(DEFAULT_ELFPATCH)
endif

ifeq ($(MKDIR),)
MKDIR := $(DEFAULT_MKDIR)
endif

#-------------------------------------------------------------------------------
#                     			构建对象的模式规则
#-------------------------------------------------------------------------------

define compile.c
@$(ECHO) "CC: $< -> $@"
@$(MKDIR) $(@D)
$(Q) $(CC) -MP -MMD -c $(APP_CPPFLAGS) $(APP_CFLAGS) -o $@ $<
$(CC_POST_PROCESS)
endef

define compile.cpp
@$(ECHO) "CXX: $< -> $@"
@$(MKDIR) $(@D)
$(Q) $(CXX) -MP -MMD -c $(APP_CPPFLAGS) $(APP_CXXFLAGS) $(APP_CFLAGS) -o $@ $<
$(CXX_POST_PROCESS)
endef

# 如果使用编译器进行汇编，必须确保给所有APP_ASFLAGS选项添加"-Wa,"前缀
ifeq ($(AS),$(patsubst %as,%,$(AS)))
COMMA := ,
APP_ASFLAGS :=  $(filter-out $(APP_CFLAGS),$(addprefix -Wa$(COMMA),$(patsubst -Wa$(COMMA)%,%,$(APP_ASFLAGS))))
endif

define compile.s
@$(ECHO) "AS: $< -> $@"
@$(MKDIR) $(@D)
$(Q) $(AS) -MP -MMD -c $(APP_CPPFLAGS) $(APP_CFLAGS) $(APP_ASFLAGS) -o $@ $<
$(AS_POST_PROCESS)
endef

ifeq ($(MAKE_VERSION),3.81)
.SECONDEXPANSION:

$(APP_OBJS_C): $(DIR_OUTPUT)/%.o: $$(call adjust-path-to-windows,%.c)
	$(compile.c)

$(APP_OBJS_CPP): $(DIR_OUTPUT)/%.o: $$(call adjust-path-to-windows,%.cpp)
	$(compile.cpp)

$(APP_OBJS_CC): $(DIR_OUTPUT)/%.o: $$(call adjust-path-to-windows,%.cc)
	$(compile.cpp)

$(APP_OBJS_CXX): $(DIR_OUTPUT)/%.o: $$(call adjust-path-to-windows,%.cxx)
	$(compile.cpp)

$(APP_OBJS_S): $(DIR_OUTPUT)/%.o: $$(call adjust-path-to-windows,%.S)
	$(compile.s)

$(APP_OBJS_SS): $(DIR_OUTPUT)/%.o: $$(call adjust-path-to-windows,%.s)
	$(compile.s)

endif # MAKE_VERSION != 3.81

$(DIR_OUTPUT)/%.o: %.c
	$(compile.c)

$(DIR_OUTPUT)/%.o: %.cpp
	$(compile.cpp)

$(DIR_OUTPUT)/%.o: %.cc
	$(compile.cpp)

$(DIR_OUTPUT)/%.o: %.cxx
	$(compile.cpp)

$(DIR_OUTPUT)/%.o: %.S
	$(compile.s)

$(DIR_OUTPUT)/%.o: %.s
	$(compile.s)


#-------------------------------------------------------------------------------
#                     			中间文件的模式规则
#-------------------------------------------------------------------------------

$(DIR_OUTPUT)/%.s: %.c
	@$(ECHO) "CPP: $< -> $@"
	@$(MKDIR) $(@D)
	$(Q) $(CC) -S $(APP_CPPFLAGS) $(APP_CFLAGS) -o $@ $<

$(DIR_OUTPUT)/%.s: %.cpp
	@$(ECHO) "CPP: $< -> $@"
	@$(MKDIR) $(@D)
	$(Q) $(CXX) -S $(APP_CPPFLAGS) $(APP_CXXFLAGS) $(APP_CFLAGS) -o $@ $<

$(DIR_OUTPUT)/%.s: %.cc
	@$(ECHO) "CPP: $< -> $@"
	@$(MKDIR) $(@D)
	$(Q) $(CXX) -S $(APP_CPPFLAGS) $(APP_CXXFLAGS) $(APP_CFLAGS) -o $@ $<

$(DIR_OUTPUT)/%.s: %.cxx
	@$(ECHO) "CPP: $< -> $@"
	@$(MKDIR) $(@D)
	$(Q) $(CXX) -S $(APP_CPPFLAGS) $(APP_CXXFLAGS) $(APP_CFLAGS) -o $@ $<

$(DIR_OUTPUT)/%.i: %.c
	@$(ECHO) "CPP: $< -> $@"
	@$(MKDIR) $(@D)
	$(Q) $(CC) -E $(APP_CPPFLAGS) $(APP_CFLAGS) -o $@ $<

$(DIR_OUTPUT)/%.i: %.cpp
	@$(ECHO) "CPP: $< -> $@"
	@$(MKDIR) $(@D)
	$(Q) $(CXX) -E $(APP_CPPFLAGS) $(APP_CXXFLAGS) $(APP_CFLAGS) -o $@ $<

$(DIR_OUTPUT)/%.i: %.cc
	@$(ECHO) "CPP: $< -> $@"
	@$(MKDIR) $(@D)
	$(Q) $(CXX) -E $(APP_CPPFLAGS) $(APP_CXXFLAGS) $(APP_CFLAGS) -o $@ $<

$(DIR_OUTPUT)/%.i: %.cxx
	@$(ECHO) "CPP: $< -> $@"
	@$(MKDIR) $(@D)
	$(Q) $(CXX) -E $(APP_CPPFLAGS) $(APP_CXXFLAGS) $(APP_CFLAGS) -o $@ $<


#-------------------------------------------------------------------------------
#                        TARGET RULES
#-------------------------------------------------------------------------------

.PHONY : help
help :
	@$(ECHO) "Summary of Makefile targets"
	@$(ECHO) "  Build targets:"
	@$(ECHO) "    all (default)     - Application and all libraries"
	@$(ECHO) "    libs              - All libraries (including BSP)"
	@$(ECHO)
	@$(ECHO) "  Clean targets:"
	@$(ECHO) "    clean_all         - Application and all libraries"
	@$(ECHO) "    clean             - Just the application"
	@$(ECHO) "    clean_libs        - All libraries"
	@$(ECHO)
	@$(ECHO) "  Run targets:"
	@$(ECHO) "    run               - Run your elf executable"

# 跳过制作库而只制作应用程序的便捷规则。
.PHONY: app
app: $(ELF)

ifeq ($(CREATE_OBJDUMP), 1)
app: $(OBJDUMP_NAME) $(ASM_NAME)
endif

# ifeq ($(CREATE_ELF_DERIVED_FILES),1)
# app: elf_derived_files
# endif
# 
# .PHONY: elf_derived_files
# elf_derived_files: default_mem_init

# 仅制作 BSP 的便捷规则。
# .PHONY : bsp
# bsp :
# 	@$(ECHO) Info: Building $(LIB_ROOT_DIR)
# 	@$(MAKE) --no-print-directory -C $(LIB_ROOT_DIR)


# Make sure all makeable libraries (including the BSP) are up-to-date.
LIB_TARGETS := $(patsubst %,%-recurs-make-lib,$(DIRS_MAKEABLE_LIBRARY))

.PHONY: libs
libs: $(LIB_TARGETS)

# 通过make -C XXX来进入XXX目录执行Makefile文件来编译库
ifneq ($(strip $(LIB_TARGETS)),)
$(LIB_TARGETS): %-recurs-make-lib:
	@$(ECHO) Info: Building $*
	$(MAKE) -C $*
endif

ifneq ($(strip $(APP_LDDEPS)),)
$(APP_LDDEPS): libs
	@true
endif

# 强制项目重建或重新链接的规则
# .force_relink文件将导致任何依赖此项目的应用程序重新链接
# .force_rebuild文件将导致此项目重建目标文件
# .force_rebuild_all文件将导致这个项目和任何依赖这个项目的项目重建目标文件

FORCE_RELINK_DEP  := .force_relink
FORCE_REBUILD_DEP := .force_rebuild
FORCE_REBUILD_ALL_DEP := .force_rebuild_all
FORCE_REBUILD_DEP_LIST := $(DIR_OUTPUT)/$(FORCE_RELINK_DEP) $(DIR_OUTPUT)/$(FORCE_REBUILD_DEP) $(FORCE_REBUILD_ALL_DEP)

$(FORCE_REBUILD_DEP_LIST):

$(APP_OBJS): $(wildcard $(DIR_OUTPUT)/$(FORCE_REBUILD_DEP)) $(wildcard $(addsuffix /$(FORCE_REBUILD_ALL_DEP), . $(DIRS_LIBRARY)))

$(ELF): $(wildcard $(addsuffix /$(FORCE_RELINK_DEP), $(DIR_OUTPUT) $(DIRS_LIBRARY)))


# 只清理应用程序。
.PHONY : clean
# ifeq ($(CREATE_ELF_DERIVED_FILES),1)
# clean : clean_elf_derived_files
# endif

clean :
	@$(RM) -r $(ELF) $(OBJDUMP_NAME) $(LINKER_MAP_NAME) $(OBJ_ROOT_DIR) $(RUNTIME_ROOT_DIR) $(FORCE_REBUILD_DEP_LIST)
	@$(ECHO) [$(APP_NAME) clean complete]

# # Clean just the BSP.
# .PHONY : clean_bsp
# clean_bsp :
# 	@$(ECHO) Info: Cleaning $(LIB_ROOT_DIR)
# 	@$(MAKE) --no-print-directory -C $(LIB_ROOT_DIR) clean

# 清理所有可制作的库
LIB_CLEAN_TARGETS := $(patsubst %,%-recurs-make-clean-lib,$(DIRS_MAKEABLE_LIBRARY))

.PHONY : clean_libs
clean_libs : $(LIB_CLEAN_TARGETS)

# 通过make -C XXX clean来进入XXX目录执行Makefile文件来清理库
ifneq ($(strip $(LIB_CLEAN_TARGETS)),)
$(LIB_CLEAN_TARGETS): %-recurs-make-clean-lib:
	@$(ECHO) Info: Cleaning $*
	$(MAKE) -C $* clean
endif

# .PHONY: clean_elf_derived_files
# clean_elf_derived_files: mem_init_clean

# 清理应用程序和所有可制作的库
.PHONY : clean_all
# clean_all : clean mem_init_clean clean_libs
clean_all : clean clean_libs

# 包括依赖文件,除非make目标是执行应用程序的清理
ifneq ($(firstword $(MAKECMDGOALS)),clean)
ifneq ($(firstword $(MAKECMDGOALS)),clean_all)
-include $(APP_DEPS)
endif
endif

# .PHONY : download-elf
# download-elf : $(ELF)
# 	@if [ "$(DOWNLOAD)" = "none" ]; \
# 	then \
# 		$(ECHO) Downloading $(ELF) not supported; \
# 	else \
# 		$(ECHO) Info: Downloading $(ELF); \
# 		$(DOWNLOAD) --go --cpu_name=$(CPU_NAME) $(DOWNLOAD_CABLE_FLAG) $(SOPC_SYSID_FLAG) $(DOWNLOAD_JDI_FLAG) $(WRITE_GMON_OPTION) $(ELF); \
# 	fi

# 如果规则的目标已更改并且其命令以非零退出状态退出,则删除该规则的目标
.DELETE_ON_ERROR:

# # 闪存编程命令规则
# PROGRAM_FLASH_SUFFIX := -program
# PROGRAM_FLASH_TARGET := $(addsuffix $(PROGRAM_FLASH_SUFFIX), $(FLASH_FILES))
# 
# .PHONY : program-flash
# program-flash : $(PROGRAM_FLASH_TARGET)
# 
# .PHONY : $(PROGRAM_FLASH_TARGET)
# $(PROGRAM_FLASH_TARGET) : flash
# 	@if [ "$(FLASHPROG)" = "none" ]; \
# 	then \
# 		$(ECHO) Programming flash not supported; \
# 	else \
# 		$(ECHO) Info: Programming $(basename $@).flash; \
# 		if [ -z "$($(basename $@)_EPCS_FLAGS)" ]; \
# 		then \
# 			$(ECHO) $(FLASHPROG) $(SOPC_SYSID_FLAG) --base=$($(basename $@)_START) $(basename $@).flash; \
# 			$(FLASHPROG) $(DOWNLOAD_CABLE_FLAG) $(SOPC_SYSID_FLAG) --base=$($(basename $@)_START) $(basename $@).flash; \
# 		else \
# 			$(ECHO) $(FLASHPROG) $(SOPC_SYSID_FLAG) --epcs --base=$($(basename $@)_START) $(basename $@).flash; \
# 			$(FLASHPROG) $(DOWNLOAD_CABLE_FLAG) $(SOPC_SYSID_FLAG) --epcs --base=$($(basename $@)_START) $(basename $@).flash; \
# 		fi \
# 	fi
# 
# 
# # Rules for simulating with an HDL Simulator [QSYS only]
# ifeq ($(QSYS),1)
# #Create a top level modelsim script load_sim.tcl to source generate msim_setup.tcl and copy mem initialization files
# CREATE_TOP_SIM_SCRIPT := alt-create-top-sim-script
# 
# ifeq ($(VSIM),)
# VSIM_EXE := "$(if $(VSIM_DIR),$(VSIM_DIR)/,)vsim"
# ifeq ($(ENABLE_VSIM_GUI),1)
# VSIM := $(VSIM_EXE) -gui
# else
# VSIM := $(VSIM_EXE) -c
# endif # ENABLE_VSIM_GUI == 1
# endif # VSIM not set
# 
# ifeq ($(SPD),)
# ifneq ($(ABS_QUARTUS_PROJECT_DIR),)
# ifneq ($(SOPC_NAME),)
# SPD_LOCATION = $(ABS_QUARTUS_PROJECT_DIR)/$(SOPC_NAME)_tb/$(SOPC_NAME)_tb/$(SOPC_NAME)_tb.spd
# LEGACY_SPD_LOCATION = $(ABS_QUARTUS_PROJECT_DIR)/$(SOPC_NAME)_tb.spd
# SPD = $(if $(wildcard $(SPD_LOCATION)),$(SPD_LOCATION),$(LEGACY_SPD_LOCATION))
# endif # SOPC_NAME set
# endif # ABS_QUARTUS_PROJECT_DIR set
# endif # SPD == empty string
# 
# 
# ifeq ($(LOAD_SIM_SCRIPT),)
# SIM_SCRIPT_DIR := $(RUNTIME_ROOT_DIR)/sim
# LOAD_SIM_SCRIPT := $(SIM_SCRIPT_DIR)/mentor/load_sim.tcl
# endif # LOAD_SIM_SCRIPT == empty string
# 
# ifeq ($(MAKE_VERSION),3.81)
# ABS_MEM_INIT_DESCRIPTOR_FILE := $(abspath $(MEM_INIT_DESCRIPTOR_FILE))
# else
# ABS_MEM_INIT_DESCRIPTOR_FILE := $(call adjust-path-to-windows,$(shell pwd))/$(MEM_INIT_DESCRIPTOR_FILE)
# endif
# 
# $(LOAD_SIM_SCRIPT): $(SPD) $(MEM_INIT_DESCRIPTOR_FILE)
# ifeq ($(SPD),)
# 	$(error No SPD file specified. Ensure QUARTUS_PROJECT_DIR variable is set)
# endif
# 	@$(MKDIR) $(SIM_SCRIPT_DIR)
# 	$(CREATE_TOP_SIM_SCRIPT) --spd=$(SPD) --mem-init-spd=$(abspath $(MEM_INIT_DESCRIPTOR_FILE)) --output-directory=$(SIM_SCRIPT_DIR)
# 
# VSIM_COMMAND = \
# 	cd $(dir $(LOAD_SIM_SCRIPT)) && \
# 	$(VSIM) -do "do $(notdir $(LOAD_SIM_SCRIPT)); ld; $(if $(VSIM_RUN_TIME),run ${VSIM_RUN_TIME};quit;)"
# 
# .PHONY: sim
# sim: $(LOAD_SIM_SCRIPT) mem_init_generate
# ifeq ($(LOAD_SIM_SCRIPT),)
# 	$(error LOAD_SIM_SCRIPT not set)
# endif
# 	$(VSIM_COMMAND)
# 
# endif # QSYS == 1




#-------------------------------------------------------------------------------
#                         		ELF目标规则
#-------------------------------------------------------------------------------
# 构建可执行 elf 文件的规则
$(ELF) : $(APP_OBJS) $(LINKER_SCRIPT) $(APP_LDDEPS)
	@$(ECHO) "LN: $@"
	$(LD) $(APP_LDFLAGS) $(APP_CFLAGS) -o $@ $(filter-out $(CRT0),$(APP_OBJS)) $(APP_LIBS) $(APP_BSP_DEP_LIBS)
	@$(ECHO)    | tee -a $(LINKER_MAP_NAME)
	@$(SIZE) $@ | tee -a $(LINKER_MAP_NAME)
	@$(ECHO)    | tee -a $(LINKER_MAP_NAME)

$(OBJDUMP_NAME) : $(ELF)
	@$(ECHO) Info: Creating $@
	$(OBJDUMP) $(OBJDUMP_FLAGS) $< >$@

$(ASM_NAME) : $(ELF)
	@$(ECHO) Info: Creating $@
	$(OBJDUMP) $(ASM_FLAGS) $< >$@

.PHONY: run
run: $(ELF)
	@./$<

# Function used to check variables. Use on the command line:
# make print-VARNAME
# Useful for debugging and adding features
.PHONY: print-%
print-%: ; @echo $*=$($*)
