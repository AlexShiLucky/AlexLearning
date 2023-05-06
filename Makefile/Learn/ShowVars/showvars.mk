# show makefile vars
# Usage:make -f Makefile -f showvars.mk Target
%:
	@echo '$*=$($*)'
d-%:
	@echo '$*=$($*)'
	@echo ' origin = $(origin $*)'
	@echo ' value = $(value $*)'
	@echo ' flavor = $(flavor $*)'
