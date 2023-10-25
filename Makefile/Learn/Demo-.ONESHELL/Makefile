# 只要makefile中出现.ONESHELL那么make对于所有指令都会使用同一个shell
run:
	cd file
	@cat file.text
	@echo `pwd`

.ONESHELL:

# cd file
# cat file.text
# echo `pwd`
# this is a file
# /home/duanduanlin/workspace/Pointers_on_C/doc/makefile_example/builtin_test_oneshell/file

# 你会看到，这里完全实现了先切换目录再执行其他指令的操作，而不是在多行完成的。此外我们想要隐藏指令调用是的输出是不是失败了啊！其实这时因为make在oneshell模式只会读取第一行命令的前置特殊字符如@,-,+等，然后把它应用到所有指令上去。
