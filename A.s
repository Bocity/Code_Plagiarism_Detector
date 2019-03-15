	.text
	.align 1,0x90
	.align 4,0x90
	.globl __ZNKSt5ctypeIcE8do_widenEc
	.weak_definition __ZNKSt5ctypeIcE8do_widenEc
__ZNKSt5ctypeIcE8do_widenEc:
LFB1533:
	movl	%esi, %eax
	ret
LFE1533:
	.align 4,0x90
	.globl __Z3putx
__Z3putx:
LFB8839:
	pushq	%rbp
LCFI0:
	movq	%rdi, %rsi
	pushq	%rbx
LCFI1:
	subq	$8, %rsp
LCFI2:
	movq	__ZSt4cout@GOTPCREL(%rip), %rdi
	call	__ZNSo9_M_insertIxEERSoT_
	movq	%rax, %rbp
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%rbp,%rax), %rbx
	testq	%rbx, %rbx
	je	L9
	cmpb	$0, 56(%rbx)
	je	L5
	movsbl	67(%rbx), %esi
L6:
	movq	%rbp, %rdi
	call	__ZNSo3putEc
	addq	$8, %rsp
LCFI3:
	popq	%rbx
LCFI4:
	movq	%rax, %rdi
	popq	%rbp
LCFI5:
	jmp	__ZNSo5flushEv
	.align 4,0x90
L5:
LCFI6:
	movq	%rbx, %rdi
	call	__ZNKSt5ctypeIcE13_M_widen_initEv
	movq	(%rbx), %rax
	movl	$10, %esi
	movq	48(%rax), %rax
	cmpq	__ZNKSt5ctypeIcE8do_widenEc@GOTPCREL(%rip), %rax
	je	L6
	movq	%rbx, %rdi
	call	*%rax
	movsbl	%al, %esi
	jmp	L6
L9:
	call	__ZSt16__throw_bad_castv
LFE8839:
	.align 4,0x90
	.globl __Z5inputv
__Z5inputv:
LFB8840:
	movq	__ZSt3cin@GOTPCREL(%rip), %rdi
	leaq	_n(%rip), %rsi
	jmp	__ZNSi10_M_extractIxEERSiRT_
LFE8840:
	.section __TEXT,__text_startup,regular,pure_instructions
	.align 4
	.globl _main
_main:
LFB8841:
	subq	$8, %rsp
LCFI7:
	xorl	%edi, %edi
	call	__ZNSt8ios_base15sync_with_stdioEb
	movq	__ZSt3cin@GOTPCREL(%rip), %rdi
	leaq	_n(%rip), %rsi
	movq	$0, 232(%rdi)
	call	__ZNSi10_M_extractIxEERSiRT_
	movq	_n(%rip), %rsi
	movq	__ZSt4cout@GOTPCREL(%rip), %rdi
	call	__ZNSo9_M_insertIxEERSoT_
	movq	%rax, %rdi
	call	__ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	xorl	%eax, %eax
	addq	$8, %rsp
LCFI8:
	ret
LFE8841:
	.align 4
__GLOBAL__sub_I_A.cpp:
LFB10196:
	leaq	__ZStL8__ioinit(%rip), %rdi
	subq	$8, %rsp
LCFI9:
	call	__ZNSt8ios_base4InitC1Ev
	movq	__ZNSt8ios_base4InitD1Ev@GOTPCREL(%rip), %rdi
	addq	$8, %rsp
LCFI10:
	leaq	___dso_handle(%rip), %rdx
	leaq	__ZStL8__ioinit(%rip), %rsi
	jmp	___cxa_atexit
LFE10196:
	.globl _k
	.zerofill __DATA,__pu_bss3,_k,8,3
	.globl _m
	.zerofill __DATA,__pu_bss3,_m,8,3
	.globl _n
	.zerofill __DATA,__pu_bss3,_n,8,3
	.static_data
__ZStL8__ioinit:
	.space	1
	.section __TEXT,__eh_frame,coalesced,no_toc+strip_static_syms+live_support
EH_frame1:
	.set L$set$0,LECIE1-LSCIE1
	.long L$set$0
LSCIE1:
	.long	0
	.byte	0x1
	.ascii "zR\0"
	.byte	0x1
	.byte	0x78
	.byte	0x10
	.byte	0x1
	.byte	0x10
	.byte	0xc
	.byte	0x7
	.byte	0x8
	.byte	0x90
	.byte	0x1
	.align 3
LECIE1:
LSFDE1:
	.set L$set$1,LEFDE1-LASFDE1
	.long L$set$1
LASFDE1:
	.long	LASFDE1-EH_frame1
	.quad	LFB1533-.
	.set L$set$2,LFE1533-LFB1533
	.quad L$set$2
	.byte	0
	.align 3
LEFDE1:
LSFDE3:
	.set L$set$3,LEFDE3-LASFDE3
	.long L$set$3
LASFDE3:
	.long	LASFDE3-EH_frame1
	.quad	LFB8839-.
	.set L$set$4,LFE8839-LFB8839
	.quad L$set$4
	.byte	0
	.byte	0x4
	.set L$set$5,LCFI0-LFB8839
	.long L$set$5
	.byte	0xe
	.byte	0x10
	.byte	0x86
	.byte	0x2
	.byte	0x4
	.set L$set$6,LCFI1-LCFI0
	.long L$set$6
	.byte	0xe
	.byte	0x18
	.byte	0x83
	.byte	0x3
	.byte	0x4
	.set L$set$7,LCFI2-LCFI1
	.long L$set$7
	.byte	0xe
	.byte	0x20
	.byte	0x4
	.set L$set$8,LCFI3-LCFI2
	.long L$set$8
	.byte	0xa
	.byte	0xe
	.byte	0x18
	.byte	0x4
	.set L$set$9,LCFI4-LCFI3
	.long L$set$9
	.byte	0xe
	.byte	0x10
	.byte	0x4
	.set L$set$10,LCFI5-LCFI4
	.long L$set$10
	.byte	0xe
	.byte	0x8
	.byte	0x4
	.set L$set$11,LCFI6-LCFI5
	.long L$set$11
	.byte	0xb
	.align 3
LEFDE3:
LSFDE5:
	.set L$set$12,LEFDE5-LASFDE5
	.long L$set$12
LASFDE5:
	.long	LASFDE5-EH_frame1
	.quad	LFB8840-.
	.set L$set$13,LFE8840-LFB8840
	.quad L$set$13
	.byte	0
	.align 3
LEFDE5:
LSFDE7:
	.set L$set$14,LEFDE7-LASFDE7
	.long L$set$14
LASFDE7:
	.long	LASFDE7-EH_frame1
	.quad	LFB8841-.
	.set L$set$15,LFE8841-LFB8841
	.quad L$set$15
	.byte	0
	.byte	0x4
	.set L$set$16,LCFI7-LFB8841
	.long L$set$16
	.byte	0xe
	.byte	0x10
	.byte	0x4
	.set L$set$17,LCFI8-LCFI7
	.long L$set$17
	.byte	0xe
	.byte	0x8
	.align 3
LEFDE7:
LSFDE9:
	.set L$set$18,LEFDE9-LASFDE9
	.long L$set$18
LASFDE9:
	.long	LASFDE9-EH_frame1
	.quad	LFB10196-.
	.set L$set$19,LFE10196-LFB10196
	.quad L$set$19
	.byte	0
	.byte	0x4
	.set L$set$20,LCFI9-LFB10196
	.long L$set$20
	.byte	0xe
	.byte	0x10
	.byte	0x4
	.set L$set$21,LCFI10-LCFI9
	.long L$set$21
	.byte	0xe
	.byte	0x8
	.align 3
LEFDE9:
	.mod_init_func
	.align 3
	.quad	__GLOBAL__sub_I_A.cpp
	.constructor
	.destructor
	.align 1
	.subsections_via_symbols
