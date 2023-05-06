.PHONY: all

# tools
ECHO = echo
RM   = rm -f

list = z x k y a a c c c g f e d b d b e c z 1.c 2.h
# sort函数功能
# 排序并删除重复字符串
all:
	@$(ECHO) "list: " $(list)
	@$(ECHO) "sort(list): "$(sort $(list))