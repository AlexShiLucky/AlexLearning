.PHONY: all

# tools
ECHO = echo
RM   = rm -f

str1 = a.c b.c c.c d.c

all:
	@$(ECHO) "str1: " $(str1)
	@$(ECHO) "subst(c,o,str1): " $(subst c,o,$(str1))
	@$(ECHO) "subst(.c,.o,str1): " $(subst .c,.o,$(str1))
	@$(ECHO) "str1(c=o): " $(str1:c=o)
	@$(ECHO) "str1(.c=.o): " $(str1:.c=.o)
	@$(ECHO) "str1(%.c=%.o):" $(str1:%.c=%.o)