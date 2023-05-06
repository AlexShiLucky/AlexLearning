.PHONY: all

# tools
ECHO = echo
RM   = rm -f

VPATH = src:../includes
CFLAGS += $(patsubst %,-I%,$(subst :, ,$(VPATH)))

all:
	@$(ECHO) "VPATH: " $(VPATH)
	@$(ECHO) "CFLAGS: " $(CFLAGS)