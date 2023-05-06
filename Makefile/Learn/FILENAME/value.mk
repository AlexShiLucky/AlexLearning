.PHONY: all

# tools
ECHO = echo
RM   = rm -f

FOO = $PATH
BAR = $(PATH)

all:
	@$(ECHO) $(FOO)
	@$(ECHO) $(BAR)
	@$(ECHO) $(value FOO)