.PHONY: all

# tools
ECHO = echo
RM   = rm -f

str1 =  a.c    b.c     c.c       d.c   

all:
	@$(ECHO) "str1: " /$(str1)/
	@$(ECHO) "strip(str1): " /$(strip $(str1))/