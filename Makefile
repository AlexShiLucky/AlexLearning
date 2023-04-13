#工程名称
TARGET         := crontab
CROSSPREFIX    :=

#设置编译器
CC             := $(CROSSPREFIX)gcc
#CC                := /opt/arm-none-gcc-5.4/bin/arm-none-eabi-gcc
OBJCOPY        := $(CROSSPREFIX)objcopy
#OBJCOPY           := /opt/arm-none-gcc-5.4/bin/arm-none-eabi-objcopy
SIZE           := $(CROSSPREFIX)size

#获取当前工作目录
TOP=.

#设置源文件后缀，c或cpp
EXT            := c

#设置源文件搜索路径
VPATH          += $(TOP)/source

#设置自定义源文件目录
SOURCE_DIR     := $(TOP)/source

#设置中间目标文件目录
OBJ_DIR        := $(TOP)/OBJ

#设定头文件包含目录
INC_DIRS       := $(TOP)/include

LIB_DIRS       :=

LIBS           :=

#宏定义
MACRO_DEFS     :=

#编译选项
CFLAGS          += -W -Wall -g -std=c99
ifneq ($(MACRO_DEFS),)
CFLAGS          += $(addprefix -I, $(MACRO_DEFS))
endif
ifneq ($(INC_DIRS),)
CFLAGS          += $(addprefix -I, $(INC_DIRS))
endif

#链接选项
LFLAGS          += -Wl,--start-group -lc -lm -Wl,--end-group
LFLAGS          += -static -Wl,-Map=Project.map -Wl,--gc-sections 

#链接启动文件和链接脚本
#LFLAGS         += $(TOP)/CORE/startup_stm32f10x_hd.s
#LFLAGS         += -T $(TOP)/CORE/stm32_flash.ld

#固定源文件添加
C_SRC           += $(shell find $(TOP)/source  -name '*.$(EXT)')

#自定义源文件添加
C_SRC           += main.c

#中间目标文件
#C_OBJ          += $(C_SRC:%.$(EXT)=%.o)
C_SRC_NODIR     = $(notdir $(C_SRC))
C_OBJ           = $(patsubst %.$(EXT), $(OBJ_DIR)/%.o,$(C_SRC_NODIR))

#依赖文件
C_DEP           = $(patsubst %.$(EXT), $(OBJ_DIR)/%.d,$(C_SRC_NODIR))

.PHONY: all clean rebuild run ctags

all:$(C_OBJ)
	@echo "linking object to $(TARGET)"
	@$(CC) $(C_OBJ) -o $(TARGET) $(LFLAGS)
	@$(SIZE) $(TARGET)

#静态模式
#$(C_OBJ):%.o:%.$(EXT)
#   $(CC) -c $(CFLAGS) -o $@ $<

$(OBJ_DIR)/%.o:%.$(EXT)
	@mkdir -p OBJ
	@echo "building $<"
	@$(CC) -c $(CFLAGS) -o $@ $<

-include $(C_DEP)
$(OBJ_DIR)/%.d:%.$(EXT)
	@mkdir -p OBJ
	@echo "making $@"
	@set -e;rm -f $@;$(CC) -MM $(CFLAGS) $< > $@.$$$$;sed 's,\($*\)\.o[ :]*,$(OBJ_DIR)/\1.o $(OBJ_DIR)/\1.d:,g' < $@.$$$$ > $@;rm -f $@.$$$$

clean:
	-rm -f $(TARGET)
	-rm -f $(OBJ_DIR)/*
	-rm -f $(shell find ./ -name '*.map')
	-rm -f $(shell find ./ -name '*.elf')
	-rm -f $(shell find ./ -name '*.bin')
	-rm -f $(shell find ./ -name '*.hex')

rebuild: clean all

ctags:
	@ctags -R *
