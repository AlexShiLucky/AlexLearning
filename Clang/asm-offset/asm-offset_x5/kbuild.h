#ifndef __KBUILD_H
#define __KBUILD_H

#include "config.h"

#if CONFIG_GEN_ASCII
#define DEFINE(sym, val) \
	asm volatile("\n.ascii \"->" #sym " %0 " #val "\"" : : "i" (val))

#define BLANK() asm volatile("\n.ascii \"->\"" : : )

#define OFFSET(sym, str, mem) \
	DEFINE(sym, offsetof(struct str, mem))

#define COMMENT(x) \
	asm volatile("\n.ascii \"->#" x "\"")

#else
#define DEFINE(sym, val) \
	asm volatile("\n->" #sym " %0 " #val : : "i" (val))

#define BLANK() asm volatile("\n->" : : )

#define OFFSET(sym, str, mem) \
	DEFINE(sym, offsetof(struct str, mem))

#define COMMENT(x) \
	asm volatile("\n->#" x)

#endif
#endif
