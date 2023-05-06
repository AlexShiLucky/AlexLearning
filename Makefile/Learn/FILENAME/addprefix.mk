.PHONY: all

# tools
ECHO = echo
RM   = rm -f

filelist = foo bar hacks
all:
	@$(ECHO) $(filelist)
	@$(ECHO) $(addprefix src/,$(filelist))