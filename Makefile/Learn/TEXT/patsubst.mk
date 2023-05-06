.PHONY: all

# tools
ECHO = echo
RM   = rm -f

str1 = a.c b.c c.c d.c
str2 = a.c b.c c.c d.c %.c

all:
	@$(ECHO) str1=$(str1)
	@$(ECHO) $(patsubst %.c,%.o,$(str1))
	@$(ECHO) $(str1:%.c=%.o)

	@$(ECHO) str2=$(str2)
	@$(ECHO) $(patsubst %.c,%.o,$(str2))
	@$(ECHO) $(str2:%.c=\%x%.o)

	@$(ECHO) str2=$(str2)
	@$(ECHO) $(patsubst %.c,%.o,$(str2))
	@$(ECHO) $(str2:%.c=%x%.o)