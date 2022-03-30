	.file	"02this.cpp"
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.rodata
.LC0:
	.string	"Animal()"
.globl _Unwind_Resume
	.section	.text._ZN6AnimalC2ESsi,"axG",@progbits,_ZN6AnimalC5ESsi,comdat
	.align 2
	.weak	_ZN6AnimalC2ESsi
	.type	_ZN6AnimalC2ESsi, @function
_ZN6AnimalC2ESsi:
.LFB958:
	.cfi_startproc
	.cfi_personality 0x0,__gxx_personality_v0
	.cfi_lsda 0x0,.LLSDA958
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%esi
	pushl	%ebx
	subl	$16, %esp
	movl	8(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
.LEHB0:
	.cfi_offset 3, -16
	.cfi_offset 6, -12
	call	_ZNSsC1ERKSs
.LEHE0:
	movl	8(%ebp), %eax
	movl	16(%ebp), %edx
	movl	%edx, 4(%eax)
	movl	$.LC0, 4(%esp)
	movl	$_ZSt4cout, (%esp)
.LEHB1:
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	8(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_ZNSolsEPKv
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, 4(%esp)
	movl	%eax, (%esp)
	call	_ZNSolsEPFRSoS_E
.LEHE1:
	jmp	.L6
.L5:
.L3:
	movl	%edx, %ebx
	movl	%eax, %esi
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZNSsD1Ev
	movl	%esi, %eax
	movl	%ebx, %edx
	movl	%eax, (%esp)
.LEHB2:
	call	_Unwind_Resume
.LEHE2:
.L6:
	addl	$16, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%esi
	.cfi_restore 6
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE958:
	.size	_ZN6AnimalC2ESsi, .-_ZN6AnimalC2ESsi
.globl __gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA958:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE958-.LLSDACSB958
.LLSDACSB958:
	.uleb128 .LEHB0-.LFB958
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0x0
	.uleb128 0x0
	.uleb128 .LEHB1-.LFB958
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L5-.LFB958
	.uleb128 0x0
	.uleb128 .LEHB2-.LFB958
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0x0
	.uleb128 0x0
.LLSDACSE958:
	.section	.text._ZN6AnimalC2ESsi,"axG",@progbits,_ZN6AnimalC5ESsi,comdat
	.weak	_ZN6AnimalC1ESsi
	.set	_ZN6AnimalC1ESsi,_ZN6AnimalC2ESsi
	.section	.rodata
.LC1:
	.string	"show() "
.LC2:
	.string	","
	.section	.text._ZN6Animal4showEv,"axG",@progbits,_ZN6Animal4showEv,comdat
	.align 2
	.weak	_ZN6Animal4showEv
	.type	_ZN6Animal4showEv, @function
_ZN6Animal4showEv:
.LFB960:
	.cfi_startproc
	.cfi_personality 0x0,__gxx_personality_v0
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$20, %esp
	movl	$.LC1, 4(%esp)
	movl	$_ZSt4cout, (%esp)
	.cfi_offset 3, -12
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	8(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_ZNSolsEPKv
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, 4(%esp)
	movl	%eax, (%esp)
	call	_ZNSolsEPFRSoS_E
	movl	8(%ebp), %eax
	movl	4(%eax), %ebx
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$_ZSt4cout, (%esp)
	call	_ZStlsIcSt11char_traitsIcESaIcEERSt13basic_ostreamIT_T0_ES7_RKSbIS4_S5_T1_E
	movl	$.LC2, 4(%esp)
	movl	%eax, (%esp)
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	%ebx, 4(%esp)
	movl	%eax, (%esp)
	call	_ZNSolsEi
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, 4(%esp)
	movl	%eax, (%esp)
	call	_ZNSolsEPFRSoS_E
	addl	$20, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE960:
	.size	_ZN6Animal4showEv, .-_ZN6Animal4showEv
	.section	.text._ZN6AnimalD2Ev,"axG",@progbits,_ZN6AnimalD5Ev,comdat
	.align 2
	.weak	_ZN6AnimalD2Ev
	.type	_ZN6AnimalD2Ev, @function
_ZN6AnimalD2Ev:
.LFB963:
	.cfi_startproc
	.cfi_personality 0x0,__gxx_personality_v0
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZNSsD1Ev
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE963:
	.size	_ZN6AnimalD2Ev, .-_ZN6AnimalD2Ev
	.weak	_ZN6AnimalD1Ev
	.set	_ZN6AnimalD1Ev,_ZN6AnimalD2Ev
	.section	.rodata
.LC3:
	.string	"xiaoqiang"
.LC4:
	.string	"xiaoxiao"
.LC5:
	.string	"&dog: "
.LC6:
	.string	"&dog1: "
	.text
.globl main
	.type	main, @function
main:
.LFB961:
	.cfi_startproc
	.cfi_personality 0x0,__gxx_personality_v0
	.cfi_lsda 0x0,.LLSDA961
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	pushl	%esi
	pushl	%ebx
	subl	$56, %esp
	leal	39(%esp), %eax
	movl	%eax, (%esp)
	.cfi_escape 0x10,0x3,0x7,0x75,0x0,0x9,0xf0,0x1a,0x38,0x1c
	.cfi_escape 0x10,0x6,0x7,0x75,0x0,0x9,0xf0,0x1a,0x34,0x1c
	call	_ZNSaIcEC1Ev
	leal	39(%esp), %eax
	movl	%eax, 8(%esp)
	movl	$.LC3, 4(%esp)
	leal	32(%esp), %eax
	movl	%eax, (%esp)
.LEHB3:
	call	_ZNSsC1EPKcRKSaIcE
.LEHE3:
	movl	$2, 8(%esp)
	leal	32(%esp), %eax
	movl	%eax, 4(%esp)
	leal	24(%esp), %eax
	movl	%eax, (%esp)
.LEHB4:
	call	_ZN6AnimalC1ESsi
.LEHE4:
	jmp	.L36
.L34:
.L14:
	movl	%edx, %ebx
	movl	%eax, %esi
	leal	32(%esp), %eax
	movl	%eax, (%esp)
	call	_ZNSsD1Ev
	movl	%esi, %eax
	movl	%ebx, %edx
	jmp	.L17
.L36:
	leal	32(%esp), %eax
	movl	%eax, (%esp)
.LEHB5:
	call	_ZNSsD1Ev
.LEHE5:
	jmp	.L37
.L33:
.L16:
	movl	%edx, %ebx
	movl	%eax, %esi
	leal	24(%esp), %eax
	movl	%eax, (%esp)
	call	_ZN6AnimalD1Ev
	movl	%esi, %eax
	movl	%ebx, %edx
	jmp	.L17
.L35:
.L17:
	movl	%edx, %ebx
	movl	%eax, %esi
	leal	39(%esp), %eax
	movl	%eax, (%esp)
	call	_ZNSaIcED1Ev
	movl	%esi, %eax
	movl	%ebx, %edx
	movl	%eax, (%esp)
.LEHB6:
	call	_Unwind_Resume
.LEHE6:
.L37:
	leal	39(%esp), %eax
	movl	%eax, (%esp)
	call	_ZNSaIcED1Ev
	leal	47(%esp), %eax
	movl	%eax, (%esp)
	call	_ZNSaIcEC1Ev
	leal	47(%esp), %eax
	movl	%eax, 8(%esp)
	movl	$.LC4, 4(%esp)
	leal	40(%esp), %eax
	movl	%eax, (%esp)
.LEHB7:
	call	_ZNSsC1EPKcRKSaIcE
.LEHE7:
	movl	$3, 8(%esp)
	leal	40(%esp), %eax
	movl	%eax, 4(%esp)
	leal	16(%esp), %eax
	movl	%eax, (%esp)
.LEHB8:
	call	_ZN6AnimalC1ESsi
.LEHE8:
	jmp	.L38
.L30:
.L19:
	movl	%edx, %ebx
	movl	%eax, %esi
	leal	40(%esp), %eax
	movl	%eax, (%esp)
	call	_ZNSsD1Ev
	movl	%esi, %eax
	movl	%ebx, %edx
	jmp	.L22
.L38:
	leal	40(%esp), %eax
	movl	%eax, (%esp)
.LEHB9:
	call	_ZNSsD1Ev
.LEHE9:
	jmp	.L39
.L29:
.L21:
	movl	%edx, %ebx
	movl	%eax, %esi
	leal	16(%esp), %eax
	movl	%eax, (%esp)
	call	_ZN6AnimalD1Ev
	movl	%esi, %eax
	movl	%ebx, %edx
	jmp	.L22
.L31:
.L22:
	movl	%edx, %ebx
	movl	%eax, %esi
	leal	47(%esp), %eax
	movl	%eax, (%esp)
	call	_ZNSaIcED1Ev
	movl	%esi, %eax
	movl	%ebx, %edx
	jmp	.L26
.L39:
	leal	47(%esp), %eax
	movl	%eax, (%esp)
	call	_ZNSaIcED1Ev
	movl	$.LC5, 4(%esp)
	movl	$_ZSt4cout, (%esp)
.LEHB10:
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	leal	24(%esp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_ZNSolsEPKv
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, 4(%esp)
	movl	%eax, (%esp)
	call	_ZNSolsEPFRSoS_E
	leal	24(%esp), %eax
	movl	%eax, (%esp)
	call	_ZN6Animal4showEv
	movl	$.LC6, 4(%esp)
	movl	$_ZSt4cout, (%esp)
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	leal	16(%esp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_ZNSolsEPKv
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, 4(%esp)
	movl	%eax, (%esp)
	call	_ZNSolsEPFRSoS_E
	leal	16(%esp), %eax
	movl	%eax, (%esp)
	call	_ZN6Animal4showEv
.LEHE10:
	jmp	.L40
.L28:
.L24:
	movl	%edx, %ebx
	movl	%eax, %esi
	leal	16(%esp), %eax
	movl	%eax, (%esp)
	call	_ZN6AnimalD1Ev
	movl	%esi, %eax
	movl	%ebx, %edx
	jmp	.L26
.L40:
	leal	16(%esp), %eax
	movl	%eax, (%esp)
.LEHB11:
	call	_ZN6AnimalD1Ev
.LEHE11:
	jmp	.L41
.L32:
.L26:
	movl	%edx, %ebx
	movl	%eax, %esi
	leal	24(%esp), %eax
	movl	%eax, (%esp)
	call	_ZN6AnimalD1Ev
	movl	%esi, %eax
	movl	%ebx, %edx
	movl	%eax, (%esp)
.LEHB12:
	call	_Unwind_Resume
.L41:
	leal	24(%esp), %eax
	movl	%eax, (%esp)
	call	_ZN6AnimalD1Ev
.LEHE12:
	movl	$0, %eax
	addl	$56, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%esi
	.cfi_restore 6
	movl	%ebp, %esp
	.cfi_def_cfa_register 4
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE961:
	.size	main, .-main
	.section	.gcc_except_table
.LLSDA961:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE961-.LLSDACSB961
.LLSDACSB961:
	.uleb128 .LEHB3-.LFB961
	.uleb128 .LEHE3-.LEHB3
	.uleb128 .L35-.LFB961
	.uleb128 0x0
	.uleb128 .LEHB4-.LFB961
	.uleb128 .LEHE4-.LEHB4
	.uleb128 .L34-.LFB961
	.uleb128 0x0
	.uleb128 .LEHB5-.LFB961
	.uleb128 .LEHE5-.LEHB5
	.uleb128 .L33-.LFB961
	.uleb128 0x0
	.uleb128 .LEHB6-.LFB961
	.uleb128 .LEHE6-.LEHB6
	.uleb128 0x0
	.uleb128 0x0
	.uleb128 .LEHB7-.LFB961
	.uleb128 .LEHE7-.LEHB7
	.uleb128 .L31-.LFB961
	.uleb128 0x0
	.uleb128 .LEHB8-.LFB961
	.uleb128 .LEHE8-.LEHB8
	.uleb128 .L30-.LFB961
	.uleb128 0x0
	.uleb128 .LEHB9-.LFB961
	.uleb128 .LEHE9-.LEHB9
	.uleb128 .L29-.LFB961
	.uleb128 0x0
	.uleb128 .LEHB10-.LFB961
	.uleb128 .LEHE10-.LEHB10
	.uleb128 .L28-.LFB961
	.uleb128 0x0
	.uleb128 .LEHB11-.LFB961
	.uleb128 .LEHE11-.LEHB11
	.uleb128 .L32-.LFB961
	.uleb128 0x0
	.uleb128 .LEHB12-.LFB961
	.uleb128 .LEHE12-.LEHB12
	.uleb128 0x0
	.uleb128 0x0
.LLSDACSE961:
	.text
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB1006:
	.cfi_startproc
	.cfi_personality 0x0,__gxx_personality_v0
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	cmpl	$1, 8(%ebp)
	jne	.L44
	cmpl	$65535, 12(%ebp)
	jne	.L44
	movl	$_ZStL8__ioinit, (%esp)
	call	_ZNSt8ios_base4InitC1Ev
	movl	$_ZNSt8ios_base4InitD1Ev, %eax
	movl	$__dso_handle, 8(%esp)
	movl	$_ZStL8__ioinit, 4(%esp)
	movl	%eax, (%esp)
	call	__cxa_atexit
.L44:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1006:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__I_main, @function
_GLOBAL__I_main:
.LFB1007:
	.cfi_startproc
	.cfi_personality 0x0,__gxx_personality_v0
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	$65535, 4(%esp)
	movl	$1, (%esp)
	call	_Z41__static_initialization_and_destruction_0ii
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1007:
	.size	_GLOBAL__I_main, .-_GLOBAL__I_main
	.section	.ctors,"aw",@progbits
	.align 4
	.long	_GLOBAL__I_main
	.section	.rodata
	.align 4
	.type	_ZZL18__gthread_active_pvE20__gthread_active_ptr, @object
	.size	_ZZL18__gthread_active_pvE20__gthread_active_ptr, 4
_ZZL18__gthread_active_pvE20__gthread_active_ptr:
	.long	_ZL22__gthrw_pthread_cancelm
	.weakref	_ZL20__gthrw_pthread_oncePiPFvvE,pthread_once
	.weakref	_ZL27__gthrw_pthread_getspecificj,pthread_getspecific
	.weakref	_ZL27__gthrw_pthread_setspecificjPKv,pthread_setspecific
	.weakref	_ZL22__gthrw_pthread_createPmPK14pthread_attr_tPFPvS3_ES3_,pthread_create
	.weakref	_ZL20__gthrw_pthread_joinmPPv,pthread_join
	.weakref	_ZL21__gthrw_pthread_equalmm,pthread_equal
	.weakref	_ZL20__gthrw_pthread_selfv,pthread_self
	.weakref	_ZL22__gthrw_pthread_detachm,pthread_detach
	.weakref	_ZL22__gthrw_pthread_cancelm,pthread_cancel
	.weakref	_ZL19__gthrw_sched_yieldv,sched_yield
	.weakref	_ZL26__gthrw_pthread_mutex_lockP15pthread_mutex_t,pthread_mutex_lock
	.weakref	_ZL29__gthrw_pthread_mutex_trylockP15pthread_mutex_t,pthread_mutex_trylock
	.weakref	_ZL31__gthrw_pthread_mutex_timedlockP15pthread_mutex_tPK8timespec,pthread_mutex_timedlock
	.weakref	_ZL28__gthrw_pthread_mutex_unlockP15pthread_mutex_t,pthread_mutex_unlock
	.weakref	_ZL26__gthrw_pthread_mutex_initP15pthread_mutex_tPK19pthread_mutexattr_t,pthread_mutex_init
	.weakref	_ZL29__gthrw_pthread_mutex_destroyP15pthread_mutex_t,pthread_mutex_destroy
	.weakref	_ZL30__gthrw_pthread_cond_broadcastP14pthread_cond_t,pthread_cond_broadcast
	.weakref	_ZL27__gthrw_pthread_cond_signalP14pthread_cond_t,pthread_cond_signal
	.weakref	_ZL25__gthrw_pthread_cond_waitP14pthread_cond_tP15pthread_mutex_t,pthread_cond_wait
	.weakref	_ZL30__gthrw_pthread_cond_timedwaitP14pthread_cond_tP15pthread_mutex_tPK8timespec,pthread_cond_timedwait
	.weakref	_ZL28__gthrw_pthread_cond_destroyP14pthread_cond_t,pthread_cond_destroy
	.weakref	_ZL26__gthrw_pthread_key_createPjPFvPvE,pthread_key_create
	.weakref	_ZL26__gthrw_pthread_key_deletej,pthread_key_delete
	.weakref	_ZL30__gthrw_pthread_mutexattr_initP19pthread_mutexattr_t,pthread_mutexattr_init
	.weakref	_ZL33__gthrw_pthread_mutexattr_settypeP19pthread_mutexattr_ti,pthread_mutexattr_settype
	.weakref	_ZL33__gthrw_pthread_mutexattr_destroyP19pthread_mutexattr_t,pthread_mutexattr_destroy
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-3)"
	.section	.note.GNU-stack,"",@progbits
