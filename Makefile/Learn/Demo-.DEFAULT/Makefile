run:nothing pro1
	@echo target run is coming.

pro1:pro2
	@echo pro1 is coming.

# .DEFAULT是给那些没有任何规则的目标设置一个默认的命令。
# 考虑这样一种情况,可能有时候我们对于一些依赖的规则还没想好怎么写，或者压根就是忘了写了，而此时我们我们又想正常调试makefile的依赖关系，而此时就可以使用.DEFAULT定义一个默认的规则。这样一来可以避免make出错，二来可以在发现没有规则的依赖时做点什么，比如加个输出。
.DEFAULT:
	@echo $@ is not exist
