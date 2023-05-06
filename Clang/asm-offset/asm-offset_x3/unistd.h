#ifndef _ASM_UNISTD_H_
#define _ASM_UNISTD_H_

#ifndef __SYSCALL
#define __SYSCALL(a,b) 
#endif

/*
 * This file contains the system call numbers.
 * 
 * Note: holes are not allowed.
 */

/* at least 8 syscall per cacheline */
#define __NR_read                                0
__SYSCALL(__NR_read, sys_read)
#define __NR_write                               1
__SYSCALL(__NR_write, sys_write)
#define __NR_open                                2
__SYSCALL(__NR_open, sys_open)
#define __NR_close                               3
__SYSCALL(__NR_close, sys_close)


#endif /* _ASM_UNISTD_H_ */
