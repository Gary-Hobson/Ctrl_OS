/*
 * @Author: Hobson
 * @Date: 2021-03-18 22:44:58
 * @Description: 保存上下文，参考https://blog.csdn.net/dog250/article/details/89742140
 * @LastEditTime: 2021-03-18 22:47:23
 */

.global context_save, context_recover

context_save:
	leaq 8(%rsp), %rdx
	movq %rdx, (0)(%rdi)
	movq %rbp, (8)(%rdi)
	movq (%rsp), %rdx		
	movq %rdx, (16)(%rdi)
	movq %r12, (24)(%rdi)
	movq %r13, (32)(%rdi)
	movq %r14, (40)(%rdi)
	movq %r15, (48)(%rdi)
	movq %rdi, (56)(%rdi)
	movq $0, %rax
	retq

context_recover:
	movq (0)(%rdi), %rsp
	movq (8)(%rdi), %rbp
	movq (16)(%rdi), %rdx
	movq %rdx, (%rsp)
	movq (24)(%rdi), %r12
	movq (32)(%rdi), %r13
	movq (40)(%rdi), %r14
	movq (48)(%rdi), %r15
	movq (48)(%rdi), %rdi
	movq $1, %rax	
	retq
    