.PHONY: all

# tools
ECHO = echo
RM   = rm -f

dirs := a b c d
files := $(foreach dir,$(dirs),$(wildcard $(dir)/*))

all:
	@$(ECHO) $(files)