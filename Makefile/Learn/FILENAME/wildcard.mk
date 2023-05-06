.PHONY: all

# tools
ECHO = echo
RM   = rm -f

all:
	@$(ECHO) $(wildcard *.mk)