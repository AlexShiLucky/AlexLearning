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
VPATH          += $(TOP)/test

#设置自定义源文件目录
SOURCE_DIR     := $(TOP)/source
SOURCE_DIR     := $(TOP)/test

#设置中间目标文件目录
OUT_DIR        := $(TOP)/build

#设定头文件包含目录
INC_DIRS       := $(TOP)/include

LIB_DIRS       :=

LIBS           :=

all:
	@echo [$(TARGET) build complete]

#宏定义
MACRO_DEFS     :=
run:MACRO_DEFS += CONFIG_LOG_COLOR_EN=1
#编译选项
CFLAGS          += -W -Wall -g -std=c99
ifneq ($(MACRO_DEFS),)
CFLAGS          += $(addprefix -D, $(MACRO_DEFS))
endif
ifneq ($(INC_DIRS),)
CFLAGS          += $(addprefix -I, $(INC_DIRS))
endif

#链接选项
LFLAGS          += -Wl,--start-group -lc -lm -Wl,--end-group
LFLAGS          += -static -Wl,-Map=$(OUT_DIR)/Project.map -Wl,--gc-sections 

#链接启动文件和链接脚本
#LFLAGS         += $(TOP)/CORE/startup_stm32f10x_hd.s
#LFLAGS         += -T $(TOP)/CORE/stm32_flash.ld

#固定源文件添加
C_SRC           += $(shell find $(TOP)/source  -name '*.$(EXT)')
C_SRC           += $(shell find $(TOP)/test  -name '*.$(EXT)')

#自定义源文件添加
C_SRC           += main.c

#中间目标文件
#C_OBJ          += $(C_SRC:%.$(EXT)=%.o)
C_SRC_NODIR     = $(notdir $(C_SRC))
C_OBJ           = $(patsubst %.$(EXT), $(OUT_DIR)/%.o,$(C_SRC_NODIR))

#依赖文件
C_DEP           = $(patsubst %.$(EXT), $(OUT_DIR)/%.d,$(C_SRC_NODIR))

.PHONY: all clean rebuild run test ctags

all:$(TARGET)

$(TARGET):$(C_OBJ)
	@echo "linking object to $(TARGET)"
	@$(CC) $(C_OBJ) -o $(TARGET) $(LFLAGS)
	@$(SIZE) $(TARGET)

#静态模式
#$(C_OBJ):%.o:%.$(EXT)
#   $(CC) -c $(CFLAGS) -o $@ $<

$(OUT_DIR)/%.o:%.$(EXT)
	@mkdir -p $(OUT_DIR)
	@echo "building $<"
	@$(CC) -c $(CFLAGS) -o $@ $<

-include $(C_DEP)
$(OUT_DIR)/%.d:%.$(EXT)
	@mkdir -p $(OUT_DIR)
	@echo "making $@"
	@set -e;rm -f $@;$(CC) -MM $(CFLAGS) $< > $@.$$$$;sed 's,\($*\)\.o[ :]*,$(OUT_DIR)/\1.o $(OUT_DIR)/\1.d:,g' < $@.$$$$ > $@;rm -f $@.$$$$

clean:
	-rm -f $(TARGET) log.txt
	-rm -rf $(OUT_DIR)

rebuild: clean all

run: all
	./$(TARGET)

test:all
	./$(TARGET) > log.txt

ctags:
	@ctags -R *
