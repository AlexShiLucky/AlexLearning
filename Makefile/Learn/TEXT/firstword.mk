.PHONY: all

# tools
ECHO = echo
RM   = rm -f

list = foo start bar baz main
# firstword函数功能
# 取首单词
all:
	@$(ECHO) "list:" $(list)
	@$(ECHO) "firstword(list): " $(firstword $(list))
	@$(ECHO) "word(1,list): " $(word 1,$(list))