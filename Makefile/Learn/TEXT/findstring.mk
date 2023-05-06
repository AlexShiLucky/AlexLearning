.PHONY: all

# tools
ECHO = echo
RM   = rm -f

str1 = /cygdriver/c /cygdriver/c/x /cygdriver/d /cygdriver/e C:\demo
find = xxxx
all:
	@$(ECHO) $(str1)
	@$(ECHO) $(findstring $(find),$(str1))
	@$(ECHO) $(findstring /cygdriver,$(str1))
	@$(ECHO) $(findstring /cygdriver/c,$(str1))