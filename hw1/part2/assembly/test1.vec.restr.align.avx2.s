	.text
	.file	"test1.cpp"
	.section	.rodata.cst8,"aM",@progbits,8
	.p2align	3                               # -- Begin function _Z5test1PfS_S_i
.LCPI0_0:
	.quad	0x3e112e0be826d695              # double 1.0000000000000001E-9
	.text
	.globl	_Z5test1PfS_S_i
	.p2align	4, 0x90
	.type	_Z5test1PfS_S_i,@function
_Z5test1PfS_S_i:                        # @_Z5test1PfS_S_i
	.cfi_startproc
# %bb.0:
	pushq	%r15
	.cfi_def_cfa_offset 16
	pushq	%r14
	.cfi_def_cfa_offset 24
	pushq	%r13
	.cfi_def_cfa_offset 32
	pushq	%r12
	.cfi_def_cfa_offset 40
	pushq	%rbx
	.cfi_def_cfa_offset 48
	subq	$32, %rsp
	.cfi_def_cfa_offset 80
	.cfi_offset %rbx, -48
	.cfi_offset %r12, -40
	.cfi_offset %r13, -32
	.cfi_offset %r14, -24
	.cfi_offset %r15, -16
	movq	%rdx, %r14
	movq	%rsi, %r15
	movq	%rdi, %rbx
	leaq	8(%rsp), %rsi
	movl	$1, %edi
	callq	clock_gettime@PLT
	testl	%eax, %eax
	jne	.LBB0_8
# %bb.1:
	leaq	4096(%r14), %rax
	leaq	4096(%rbx), %rcx
	cmpq	%r14, %rcx
	seta	%cl
	leaq	4096(%r15), %rsi
	cmpq	%rbx, %rax
	seta	%dl
	andb	%cl, %dl
	cmpq	%r14, %rsi
	seta	%cl
	movq	8(%rsp), %r13
	cmpq	%r15, %rax
	seta	%al
	movq	16(%rsp), %r12
	andb	%cl, %al
	orb	%dl, %al
	xorl	%ecx, %ecx
	jmp	.LBB0_2
	.p2align	4, 0x90
.LBB0_4:                                #   in Loop: Header=BB0_2 Depth=1
	addl	$1, %ecx
	cmpl	$20000000, %ecx                 # imm = 0x1312D00
	je	.LBB0_5
.LBB0_2:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_3 Depth 2
                                        #     Child Loop BB0_7 Depth 2
	xorl	%edx, %edx
	testb	%al, %al
	je	.LBB0_3
	.p2align	4, 0x90
.LBB0_7:                                #   Parent Loop BB0_2 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	vmovss	(%rbx,%rdx,4), %xmm0            # xmm0 = mem[0],zero,zero,zero
	vaddss	(%r15,%rdx,4), %xmm0, %xmm0
	vmovss	%xmm0, (%r14,%rdx,4)
	vmovss	4(%rbx,%rdx,4), %xmm0           # xmm0 = mem[0],zero,zero,zero
	vaddss	4(%r15,%rdx,4), %xmm0, %xmm0
	vmovss	%xmm0, 4(%r14,%rdx,4)
	vmovss	8(%rbx,%rdx,4), %xmm0           # xmm0 = mem[0],zero,zero,zero
	vaddss	8(%r15,%rdx,4), %xmm0, %xmm0
	vmovss	%xmm0, 8(%r14,%rdx,4)
	vmovss	12(%rbx,%rdx,4), %xmm0          # xmm0 = mem[0],zero,zero,zero
	vaddss	12(%r15,%rdx,4), %xmm0, %xmm0
	vmovss	%xmm0, 12(%r14,%rdx,4)
	addq	$4, %rdx
	cmpq	$1024, %rdx                     # imm = 0x400
	jne	.LBB0_7
	jmp	.LBB0_4
	.p2align	4, 0x90
.LBB0_3:                                #   Parent Loop BB0_2 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	vmovaps	(%rbx,%rdx,4), %ymm0
	vmovaps	32(%rbx,%rdx,4), %ymm1
	vmovaps	64(%rbx,%rdx,4), %ymm2
	vmovaps	96(%rbx,%rdx,4), %ymm3
	vaddps	(%r15,%rdx,4), %ymm0, %ymm0
	vaddps	32(%r15,%rdx,4), %ymm1, %ymm1
	vaddps	64(%r15,%rdx,4), %ymm2, %ymm2
	vaddps	96(%r15,%rdx,4), %ymm3, %ymm3
	vmovaps	%ymm0, (%r14,%rdx,4)
	vmovaps	%ymm1, 32(%r14,%rdx,4)
	vmovaps	%ymm2, 64(%r14,%rdx,4)
	vmovaps	%ymm3, 96(%r14,%rdx,4)
	addq	$32, %rdx
	cmpq	$1024, %rdx                     # imm = 0x400
	jne	.LBB0_3
	jmp	.LBB0_4
.LBB0_5:
	leaq	8(%rsp), %rsi
	movl	$1, %edi
	vzeroupper
	callq	clock_gettime@PLT
	testl	%eax, %eax
	jne	.LBB0_8
# %bb.6:
	movq	8(%rsp), %rax
	subq	%r13, %rax
	movq	16(%rsp), %rcx
	subq	%r12, %rcx
	vcvtsi2sd	%rax, %xmm4, %xmm0
	vcvtsi2sd	%rcx, %xmm4, %xmm1
	vmulsd	.LCPI0_0(%rip), %xmm1, %xmm1
	vaddsd	%xmm0, %xmm1, %xmm0
	vmovsd	%xmm0, 24(%rsp)                 # 8-byte Spill
	movq	_ZSt4cout@GOTPCREL(%rip), %rbx
	leaq	.L.str(%rip), %rsi
	movl	$47, %edx
	movq	%rbx, %rdi
	callq	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%rbx, %rdi
	vmovsd	24(%rsp), %xmm0                 # 8-byte Reload
                                        # xmm0 = mem[0],zero
	callq	_ZNSo9_M_insertIdEERSoT_@PLT
	movq	%rax, %rbx
	leaq	.L.str.1(%rip), %rsi
	movl	$8, %edx
	movq	%rax, %rdi
	callq	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%rbx, %rdi
	movl	$1024, %esi                     # imm = 0x400
	callq	_ZNSolsEi@PLT
	movq	%rax, %rbx
	leaq	.L.str.2(%rip), %rsi
	movl	$5, %edx
	movq	%rax, %rdi
	callq	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%rbx, %rdi
	movl	$20000000, %esi                 # imm = 0x1312D00
	callq	_ZNSolsEi@PLT
	leaq	.L.str.3(%rip), %rsi
	movl	$2, %edx
	movq	%rax, %rdi
	callq	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	addq	$32, %rsp
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	retq
.LBB0_8:
	.cfi_def_cfa_offset 80
	leaq	.L.str.4(%rip), %rdi
	leaq	.L.str.5(%rip), %rsi
	leaq	.L__PRETTY_FUNCTION__._ZL7gettimev(%rip), %rcx
	movl	$75, %edx
	callq	__assert_fail@PLT
.Lfunc_end0:
	.size	_Z5test1PfS_S_i, .Lfunc_end0-_Z5test1PfS_S_i
	.cfi_endproc
                                        # -- End function
	.section	.text.startup,"ax",@progbits
	.p2align	4, 0x90                         # -- Begin function _GLOBAL__sub_I_test1.cpp
	.type	_GLOBAL__sub_I_test1.cpp,@function
_GLOBAL__sub_I_test1.cpp:               # @_GLOBAL__sub_I_test1.cpp
	.cfi_startproc
# %bb.0:
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset %rbx, -16
	leaq	_ZStL8__ioinit(%rip), %rbx
	movq	%rbx, %rdi
	callq	_ZNSt8ios_base4InitC1Ev@PLT
	movq	_ZNSt8ios_base4InitD1Ev@GOTPCREL(%rip), %rdi
	leaq	__dso_handle(%rip), %rdx
	movq	%rbx, %rsi
	popq	%rbx
	.cfi_def_cfa_offset 8
	jmp	__cxa_atexit@PLT                # TAILCALL
.Lfunc_end1:
	.size	_GLOBAL__sub_I_test1.cpp, .Lfunc_end1-_GLOBAL__sub_I_test1.cpp
	.cfi_endproc
                                        # -- End function
	.type	_ZStL8__ioinit,@object          # @_ZStL8__ioinit
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.hidden	__dso_handle
	.type	.L.str,@object                  # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"Elapsed execution time of the loop in test1():\n"
	.size	.L.str, 48

	.type	.L.str.1,@object                # @.str.1
.L.str.1:
	.asciz	"sec (N: "
	.size	.L.str.1, 9

	.type	.L.str.2,@object                # @.str.2
.L.str.2:
	.asciz	", I: "
	.size	.L.str.2, 6

	.type	.L.str.3,@object                # @.str.3
.L.str.3:
	.asciz	")\n"
	.size	.L.str.3, 3

	.type	.L.str.4,@object                # @.str.4
.L.str.4:
	.asciz	"r == 0"
	.size	.L.str.4, 7

	.type	.L.str.5,@object                # @.str.5
.L.str.5:
	.asciz	"./fasttime.h"
	.size	.L.str.5, 13

	.type	.L__PRETTY_FUNCTION__._ZL7gettimev,@object # @__PRETTY_FUNCTION__._ZL7gettimev
.L__PRETTY_FUNCTION__._ZL7gettimev:
	.asciz	"fasttime_t gettime()"
	.size	.L__PRETTY_FUNCTION__._ZL7gettimev, 21

	.section	.init_array,"aw",@init_array
	.p2align	3
	.quad	_GLOBAL__sub_I_test1.cpp
	.ident	"Ubuntu clang version 14.0.0-1ubuntu1.1"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym _GLOBAL__sub_I_test1.cpp
	.addrsig_sym _ZStL8__ioinit
	.addrsig_sym __dso_handle
	.addrsig_sym _ZSt4cout
