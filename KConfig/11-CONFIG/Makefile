.PHONY: all clean

KCONFIG := kconfig-mconf
RM := rm -rf

# 在环境变量中设置CONFIG_的值可修改生成.config中变量前缀
all:
	CONFIG_=USR_CFG_ $(KCONFIG) Kconfig

clean:
	-$(RM) .config
