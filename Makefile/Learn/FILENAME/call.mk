.PHONY: all

# tools
ECHO = echo
RM   = rm -f

reverse = $(2)$(1)

all:
	@$(ECHO) $(call reverse,a,b)