#START GENERATED
# 定义应用程序ELF的路径。
# 它可能被makefile片段使用，因此在包含它们之前定义。
# 
ELF := shape.elf

DIRS_SRCS := lib

# Paths to C, C++, and assembly source files.
C_SRCS   := main.c
C_SRCS   += $(shell find $(DIRS_SRCS) -name '*.c')
CXX_SRCS :=
ASM_SRCS :=

# Path to root of object file tree.
OBJ_ROOT_DIR := build

# Options to control objdump.
CREATE_OBJDUMP := 1
OBJDUMP_INCLUDE_SOURCE := 1
OBJDUMP_FULL_CONTENTS := 0

# Options to enable/disable optional files.
#CREATE_ELF_DERIVED_FILES := 0
CREATE_LINKER_MAP := 1

# Common arguments for ALT_CFLAGSs
APP_CFLAGS_DEFINED_SYMBOLS :=
APP_CFLAGS_UNDEFINED_SYMBOLS :=
APP_CFLAGS_OPTIMIZATION := -O0
APP_CFLAGS_DEBUG_LEVEL := -g
APP_CFLAGS_WARNINGS := -Wall -Wformat-security
APP_CFLAGS_USER_FLAGS := -std=c99 -fdata-sections -ffunction-sections

APP_ASFLAGS_USER :=
APP_LDFLAGS_USER := -Wl,-gc-sections

# Linker options that have default values assigned later if not
# assigned here.
LINKER_SCRIPT :=
CRT0 :=
SYS_LIB :=

# Define path to the root of the BSP.
LIB_ROOT_DIR :=

# List of application specific include directories, library directories and library names
APP_INCLUDE_DIRS += include
APP_INCLUDE_DIRS += lib/libshape/include
APP_LIBRARY_DIRS :=
APP_LIBRARY_NAMES :=

# Begin and End processor settings.
BUILD_BEGIN_PROCESS :=
BUILD_END_PROCESS :=


#END GENERATED
