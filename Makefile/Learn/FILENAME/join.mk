.PHONY: all

# tools
ECHO = echo
RM   = rm -f

list1 = a.c b.c c.c d.c e.c
list2 = 1.c 2.c 3.c 4.c 5.c 6.c 7.c

all:
	@$(ECHO) $(list1)
	@$(ECHO) $(list2)
	@$(ECHO) $(join $(list1),$(list2))