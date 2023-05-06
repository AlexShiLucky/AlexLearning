.PHONY: all

# tools
ECHO = echo
RM   = rm -f

filelist = src/foo src-1.0/bar /home/jack/.font hacks
all:
	@$(ECHO) $(filelist)
	@$(ECHO) $(addsuffix .c,$(filelist))