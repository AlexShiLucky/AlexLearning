.PHONY: all

# tools
ECHO = echo
RM   = rm -f

list = foo start bar baz main
# wordlist函数功能
# 取从[n,m]的单词
all:
	@$(ECHO) "list:" $(list)
	@$(ECHO) "wordlist(2,3,list):" $(wordlist 2,3,$(list))
	@$(ECHO) "wordlist(3,8,list):" $(wordlist 3,8,$(list))