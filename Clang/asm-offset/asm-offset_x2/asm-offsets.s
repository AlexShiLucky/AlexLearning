	.cpu arm7tdmi
	.arch armv4t
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"asm-offsets.c"
	.text
	.data
	.align	2
	.type	syscalls, %object
	.size	syscalls, 4
syscalls:
	.ascii	"\001\001\001\001"
	.text
	.align	2
	.global	main
	.syntax unified
	.arm
	.type	main, %function
main:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	.syntax divided
@ 25 "asm-offsets.c" 1
	
->THREAD_KSP #4 offsetof(struct thread_struct, ksp)
@ 0 "" 2
@ 26 "asm-offsets.c" 1
	
->THREAD_KPSR #8 offsetof(struct thread_struct, kpsr)
@ 0 "" 2
@ 27 "asm-offsets.c" 1
	
->
@ 0 "" 2
@ 30 "asm-offsets.c" 1
	
->PT_ORIG_R2 #60 offsetof(struct pt_regs, orig_r2)
@ 0 "" 2
@ 31 "asm-offsets.c" 1
	
->PT_ORIG_R7 #88 offsetof(struct pt_regs, orig_r7)
@ 0 "" 2
@ 33 "asm-offsets.c" 1
	
->PT_R1 #32 offsetof(struct pt_regs, r1)
@ 0 "" 2
@ 34 "asm-offsets.c" 1
	
->PT_R2 #36 offsetof(struct pt_regs, r2)
@ 0 "" 2
@ 35 "asm-offsets.c" 1
	
->PT_R3 #40 offsetof(struct pt_regs, r3)
@ 0 "" 2
@ 36 "asm-offsets.c" 1
	
->PT_R4 #44 offsetof(struct pt_regs, r4)
@ 0 "" 2
@ 37 "asm-offsets.c" 1
	
->PT_R5 #48 offsetof(struct pt_regs, r5)
@ 0 "" 2
@ 38 "asm-offsets.c" 1
	
->PT_R6 #52 offsetof(struct pt_regs, r6)
@ 0 "" 2
@ 39 "asm-offsets.c" 1
	
->PT_R7 #56 offsetof(struct pt_regs, r7)
@ 0 "" 2
@ 40 "asm-offsets.c" 1
	
->PT_R8 #0 offsetof(struct pt_regs, r8)
@ 0 "" 2
@ 41 "asm-offsets.c" 1
	
->PT_R9 #4 offsetof(struct pt_regs, r9)
@ 0 "" 2
@ 42 "asm-offsets.c" 1
	
->PT_R10 #8 offsetof(struct pt_regs, r10)
@ 0 "" 2
@ 43 "asm-offsets.c" 1
	
->PT_R11 #12 offsetof(struct pt_regs, r11)
@ 0 "" 2
@ 44 "asm-offsets.c" 1
	
->PT_R12 #16 offsetof(struct pt_regs, r12)
@ 0 "" 2
@ 45 "asm-offsets.c" 1
	
->PT_R13 #20 offsetof(struct pt_regs, r13)
@ 0 "" 2
@ 46 "asm-offsets.c" 1
	
->PT_R14 #24 offsetof(struct pt_regs, r14)
@ 0 "" 2
@ 47 "asm-offsets.c" 1
	
->PT_R15 #28 offsetof(struct pt_regs, r15)
@ 0 "" 2
@ 48 "asm-offsets.c" 1
	
->PT_EA #84 offsetof(struct pt_regs, ea)
@ 0 "" 2
@ 49 "asm-offsets.c" 1
	
->PT_RA #64 offsetof(struct pt_regs, ra)
@ 0 "" 2
@ 50 "asm-offsets.c" 1
	
->PT_FP #68 offsetof(struct pt_regs, fp)
@ 0 "" 2
@ 51 "asm-offsets.c" 1
	
->PT_SP #72 offsetof(struct pt_regs, sp)
@ 0 "" 2
@ 52 "asm-offsets.c" 1
	
->PT_GP #76 offsetof(struct pt_regs, gp)
@ 0 "" 2
@ 53 "asm-offsets.c" 1
	
->PT_ESTATUS #80 offsetof(struct pt_regs, estatus)
@ 0 "" 2
@ 54 "asm-offsets.c" 1
	
->PT_REGS_SIZE #92 sizeof(struct pt_regs)
@ 0 "" 2
@ 55 "asm-offsets.c" 1
	
->
@ 0 "" 2
@ 58 "asm-offsets.c" 1
	
->SW_R16 #0 offsetof(struct switch_stack, r16)
@ 0 "" 2
@ 59 "asm-offsets.c" 1
	
->SW_R17 #4 offsetof(struct switch_stack, r17)
@ 0 "" 2
@ 60 "asm-offsets.c" 1
	
->SW_R18 #8 offsetof(struct switch_stack, r18)
@ 0 "" 2
@ 61 "asm-offsets.c" 1
	
->SW_R19 #12 offsetof(struct switch_stack, r19)
@ 0 "" 2
@ 62 "asm-offsets.c" 1
	
->SW_R20 #16 offsetof(struct switch_stack, r20)
@ 0 "" 2
@ 63 "asm-offsets.c" 1
	
->SW_R21 #20 offsetof(struct switch_stack, r21)
@ 0 "" 2
@ 64 "asm-offsets.c" 1
	
->SW_R22 #24 offsetof(struct switch_stack, r22)
@ 0 "" 2
@ 65 "asm-offsets.c" 1
	
->SW_R23 #28 offsetof(struct switch_stack, r23)
@ 0 "" 2
@ 66 "asm-offsets.c" 1
	
->SW_FP #32 offsetof(struct switch_stack, fp)
@ 0 "" 2
@ 67 "asm-offsets.c" 1
	
->SW_GP #36 offsetof(struct switch_stack, gp)
@ 0 "" 2
@ 68 "asm-offsets.c" 1
	
->SW_RA #40 offsetof(struct switch_stack, ra)
@ 0 "" 2
@ 69 "asm-offsets.c" 1
	
->SWITCH_STACK_SIZE #44 sizeof(struct switch_stack)
@ 0 "" 2
@ 70 "asm-offsets.c" 1
	
->
@ 0 "" 2
@ 73 "asm-offsets.c" 1
	
->TI_FLAGS #4 offsetof(struct thread_info, flags)
@ 0 "" 2
@ 74 "asm-offsets.c" 1
	
->TI_PREEMPT_COUNT #12 offsetof(struct thread_info, preempt_count)
@ 0 "" 2
@ 75 "asm-offsets.c" 1
	
->
@ 0 "" 2
@ 77 "asm-offsets.c" 1
	
->__NR_syscall_max #3 sizeof(syscalls)-1
@ 0 "" 2
	.arm
	.syntax unified
	mov	r3, #0
	mov	r0, r3
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	main, .-main
	.ident	"GCC: (GNU Toolchain for the Arm Architecture 11.2-2022.02 (arm-11.14)) 11.2.1 20220111"
