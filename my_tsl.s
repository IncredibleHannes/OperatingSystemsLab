.file	"my_tsl.c"
.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
.text
.LHOTB0:
.p2align 4,,15
.globl	tsl
.type	tsl, @function
tsl:
.LFB0:
.cfi_startproc
movzbl	(%rdi), %eax
movl $1, %ebx
lock xchg %eax, %ebx
movb	%bl, (%rdi)
ret
.cfi_endproc
.LFE0:
.size	test, .-test
.section	.text.unlikely
.LCOLDE0:
.text
.LHOTE0:
.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
.section	.note.GNU-stack,"",@progbits
