.PHONY: all

# tools
ECHO = echo
RM   = rm -f

list = foo start bar baz main
# word函数功能
# 取从1开始的第N个单词
all:
	@$(ECHO) "list:" $(list)
	@$(ECHO) "word(2,list):" $(word 2,$(list))
	@$(ECHO) "word(8,list):" $(word 8,$(list))