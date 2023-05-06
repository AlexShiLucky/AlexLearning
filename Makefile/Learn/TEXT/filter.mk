.PHONY: all

# tools
ECHO = echo
RM   = rm -f

str1 = a.c a.h b.c b.h c.c c.h d.c d.h x.s

all:
	@$(ECHO) $(str1)
	@$(ECHO) $(filter %.c %.s,$(str1))