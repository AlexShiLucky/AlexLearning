# 获取顶层目录
TOPDIR := $(shell pwd | sed -e 's/ /\\ /g')

################################################################################
# mkdir目录加上-p选项可以创建包含多级目录的路径
MKDIR := mkdir -p

################################################################################
SUBDIR := $(shell ls -d */)

SUBDIR := $(shell ls ./ -l | awk '/^d/{print $NF}')
################################################################################
# 列出多级目录下所有的.c文件
CSRCS := $(shell find $(DIRS) -name '*.c')

################################################################################
# Function used to check variables. Use on the command line:
# make print-VARNAME
# Useful for debugging and adding features
.PHONY: print-%
print-%: ; @echo $*=$($*)

################################################################################

OBJS = $(sort $(addprefix $(OBJ_DIR)/,                                        \
               $(patsubst %.c, %.o,   $(patsubst %.C, %.o, $(C_SRCS)))        \
               $(patsubst %.cxx, %.o, $(patsubst %.CXX, %.o,                  \
               $(patsubst %.cc, %.o,  $(patsubst %.CC, %.o,                   \
               $(patsubst %.cpp, %.o, $(patsubst %.CPP, %.o,                  \
                 $(CXX_SRCS) ))))))                                           \
               $(patsubst %.S, %.o, $(patsubst %.s, %.o, $(ASM_SRCS))) ))