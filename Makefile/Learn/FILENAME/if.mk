.PHONY: all

# tools
ECHO = echo
RM   = rm -f

SRC_DIR = /home/micro-os/src

all:
	@$(ECHO) $(if $(SRC_DIR),$(SRC_DIR),/home/src)