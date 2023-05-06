#ifndef __TYPES_H__
#define __TYPES_H__

#define offsetof(type, member) ((int)&(((type *)0)->member))

typedef struct {
    unsigned long seg;
} mm_segment_t;

/*
 * low level task data that entry.S needs immediate access to
 * - this struct should fit entirely inside of one cache line
 * - this struct shares the supervisor stack pages
 * - if the contents of this structure are changed, the assembly constants
 *   must also be changed
 */
struct thread_info {
    void  *task;      /* main task structure */
    unsigned long       flags;      /* low level flags */
    unsigned int        cpu;        /* current CPU */
    int                 preempt_count;  /* 0 => preemptable,<0 => BUG */
    mm_segment_t        addr_limit; /* thread address space:
                          0-0x7FFFFFFF for user-thead
                          0-0xFFFFFFFF for kernel-thread
                        */
    struct pt_regs      *regs;
};

struct pt_regs {
    unsigned long  r8;  /* r8-r15 Caller-saved GP registers */
    unsigned long  r9;
    unsigned long  r10;
    unsigned long  r11;
    unsigned long  r12;
    unsigned long  r13;
    unsigned long  r14;
    unsigned long  r15;
    unsigned long  r1;  /* Assembler temporary */
    unsigned long  r2;  /* Retval LS 32bits */
    unsigned long  r3;  /* Retval MS 32bits */
    unsigned long  r4;  /* r4-r7 Register arguments */
    unsigned long  r5;
    unsigned long  r6;
    unsigned long  r7;
    unsigned long  orig_r2; /* Copy of r2 ?? */
    unsigned long  ra;  /* Return address */
    unsigned long  fp;  /* Frame pointer */
    unsigned long  sp;  /* Stack pointer */
    unsigned long  gp;  /* Global pointer */
    unsigned long  estatus;
    unsigned long  ea;  /* Exception return address (pc) */
    unsigned long  orig_r7;
};

/*
 * This is the extended stack used by signal handlers and the context
 * switcher: it's pushed after the normal "struct pt_regs".
 */
struct switch_stack {
    unsigned long  r16; /* r16-r23 Callee-saved GP registers */
    unsigned long  r17;
    unsigned long  r18;
    unsigned long  r19;
    unsigned long  r20;
    unsigned long  r21;
    unsigned long  r22;
    unsigned long  r23;
    unsigned long  fp;
    unsigned long  gp;
    unsigned long  ra;
};

struct thread_struct {
    struct pt_regs *kregs;

    /* Context switch saved kernel state. */
    unsigned long ksp;
    unsigned long kpsr;
};

#endif
