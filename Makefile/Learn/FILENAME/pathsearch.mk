.PHONY: all

# tools
ECHO = echo
RM   = rm -f

pathsearch = $(firstword $(wildcard $(addsuffix /$(1),$(subst :, ,$(PATH)))))
LS := $(call pathsearch,ls)

all:
	@$(ECHO) $(LS)