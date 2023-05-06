################################################################################
# $touch b.h
# $touch d.h
# $make
# 依据命令行的输出结果和file.dep文件的内容，我们同样来分析一下该结果的产生过程：
# 
# 首先include命令先把file.dep文件包含进Makefile文件，包含进Makefile文件的内容为file.dep:a.h。然后，在集合U中检查是否有能使得file.dep文件发生更新的规则，此时，规则
# 
# file.dep:a.h
# 
# 不能使file.dep文件发生更新，但是规则
# 
# file.dep:b.h
#     @echo "test:d.h" > file.dep;
# 
# 却可以使file.dep文件发生更新，所以include命令会将更新后的file.dep文件再次包含进Makefile文件，而更新后的file.dep文件的内容也变为test:d.h。然后继续在U中检查是否有规则能使file.dep文件发生更新，此时U中以file.dep为目标的规则只有
# 
# file.dep:b.h
#     @echo "test:d.h" > file.dep;
# 
# 并且此时的file.dep比b.h新，所以该规则中的命令不会被执行且该规则也不能使file.dep文件发生更新，include命令到此执行结束，最终包含在Makefile文件的内容为test:d.h。
# 
# 　　接下来就是去执行all目标的规则了，all依赖于test，此时Makefile文件中有两条以test为目标的规则：
# 
# test:d.h和
# 
# test:c.h
#     touch test;
# 
# 此时test比c.h新，而d.h比test新，根据文件的新旧关系以及实验一可知，最后会输出“touch test;”，并且该命令的执行是由依赖关系test:d.h触发的。
# 
# 　　以上实验说明：如果在集合U（这里是U1）中存在以file.dep为目标的规则，并且该规则使得file.dep发生了更新，则file.dep文件会被再次包含进Makefile文件。
################################################################################

all:test

include file.dep

file.dep: b.h
	@echo "test:d.h" > file.dep

test: c.h
	@echo "This is c.h."
	touch test
