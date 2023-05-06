# .RECIPEPREFIX可以修改命令默认前缀,为空是表示tab
.PHONY: all
.RECIPEPREFIX = >
all:
> @echo Hello, world！

.RECIPEPREFIX = <
hello:
< @echo Hello, world！

.RECIPEPREFIX = 
world:
	@echo Hello, world！
