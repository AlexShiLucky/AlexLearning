# define和=可以用于定义函数,参数使用$(n)来引用
.PHONY: all
define fun1
@echo "My name is $(0)"
endef

define fun2
@echo "My name is $(0), param is $(1)"
endef

define fun3
@echo "My name is $(0), param1 is $(1), param2 is $(2)"
endef

fun4 = @echo "My name is $(0), param is $(1)"

# :=不能用于定义函数
fun5 := @echo "My name is $(0), param is $(1)"

var1 := $(call fun1)    
var2 := $(fun1)

all:
	$(call fun1)
	$(call fun2,hello Makefile!)
	$(call fun3,A,B)
	$(call fun4,hello Makefile!)
	$(call fun5,hello Makefile!)
	@echo "var1 => $(var1)"   
	@echo "var2 => $(var2)" 
