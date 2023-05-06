################################################################################
# $ touch a.h(b.h,c.h,由于输出结果一样，这里为节省篇幅写在一行)
# $ make
# Makefile:6: warning: overriding commands for target `test'
# Makefile:4: warning: ignoring old commands for target `test'
# Makefile:8: warning: overriding commands for target `test'
# Makefile:6: warning: ignoring old commands for target `test'
# this is c.h
# touch test;
# 从执行结果可以看出，只有最后一条规则的命令得到了执行。
# 
# 　　以上实验说明：在同一Makefile文件中，如果有两个或两个以上规则具有相同的目标，
# 则在这些规则中，任一规则中的依赖文件的更新都会且仅会导致最后一个规则中的命令被
# 执行，前面规则的命令被忽略。
################################################################################

all:test

include file.dep

test: b.h
	@echo "This is b.h."

test: c.h
	@echo "This is c.h."
	touch test
