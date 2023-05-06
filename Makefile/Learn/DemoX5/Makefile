################################################################################
# $ touch a.h
# $ make
# hello world
# touch test;
# 
# $ touch b.h
# $ make
# hello world
# touch test;
# 
# $ touch c.h
# $ make
# hello world
# touch test;
# 
# 从命令行输出可知，每次都输出了“hello world”并且更新了test文件。
# 
# 　　以上实验说明：在同一个Makefile文件中，如果两个或两个以上规则具有相同的目标，
# 则在这些规则中，任一规则中的依赖文件的更新都会导致规则中的命令被执行。
################################################################################

all:test

test: a.h
test: b.h
test: c.h
	@echo "Hello Makefile."
	touch test

