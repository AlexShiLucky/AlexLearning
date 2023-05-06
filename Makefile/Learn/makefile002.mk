.PHONY: all
#TOPDIR := $(shell echo %CD%)
TOPDIR := ${shell pwd | sed -e 's/ /\\ /g'}
all:
	@$(pwd)
	@echo $(TOPDIR)
