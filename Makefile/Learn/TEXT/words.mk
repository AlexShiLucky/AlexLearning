.PHONY: all

# tools
ECHO = echo
RM   = rm -f

list = foo start bar baz main
# words函数功能
# 单词个数
all:
	@$(ECHO) "list: " $(list)
	@$(ECHO) "words(list): " $(words $(list))