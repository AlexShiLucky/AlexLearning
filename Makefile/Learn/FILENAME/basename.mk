.PHONY: all

# tools
ECHO = echo
RM   = rm -f

filelist = src/foo src-1.0/bar.c /home/jack/.font.cache-1 hacks
all:
	@$(ECHO) $(filelist)
	@$(ECHO) $(basename $(filelist))