.PHONY: all

# tools
ECHO = echo
RM   = rm -f

filelist =  src/a.c \
			src/b.c \
			src/b/	\
			src/b/	\
			src/c.c \
			src/c/	\
			src/d.c \
			src/e.c \
			main.c
all:
	@$(ECHO) $(filelist)
	@$(ECHO) $(notdir $(filelist))