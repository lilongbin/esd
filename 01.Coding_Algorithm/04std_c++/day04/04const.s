	.file	"04const.cpp"
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.rodata
.LC0:
	.string	"show()"
	.section	.text._ZN1A4showEv,"axG",@progbits,_ZN1A4showEv,comdat
	.align 2
	.weak	_ZN1A4showEv
	.type	_ZN1A4showEv, @function
_ZN1A4showEv:
.LFB957:
	.cfi_startproc
	.cfi_personality 0x0,__gxx_personality_v0
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	$10, (%eax)
	movl	$.LC0, 4(%esp)
	movl	$_ZSt4cout, (%esp)
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, 4(%esp)
	movl	%eax, (%esp)
	call	_ZNSolsEPFRSoS_E
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE957:
	.size	_ZN1A4showEv, .-_ZN1A4showEv
	.section	.rodata
.LC1:
	.string	"const show()"
	.section	.text._ZNK1A4showEv,"axG",@progbits,_ZNK1A4showEv,comdat
	.align 2
	.weak	_ZNK1A4showEv
	.type	_ZNK1A4showEv, @function
_ZNK1A4showEv:
.LFB958:
	.cfi_startproc
	.cfi_personality 0x0,__gxx_personality_v0
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	$20, (%eax)
	movl	$.LC1, 4(%esp)
	movl	$_ZSt4cout, (%esp)
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, 4(%esp)
	movl	%eax, (%esp)
	call	_ZNSolsEPFRSoS_E
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE958:
	.size	_ZNK1A4showEv, .-_ZNK1A4showEv
	.text
.globl main
	.type	main, @function
main:
.LFB959:
	.cfi_startproc
	.cfi_personality 0x0,__gxx_personality_v0
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$32, %esp
	leal	28(%esp), %eax
	movl	%eax, (%esp)
	call	_ZN1A4showEv
	movl	28(%esp), %eax
	movl	%eax, 24(%esp)
	leal	24(%esp), %eax
	movl	%eax, (%esp)
	call	_ZNK1A4showEv
	movl	$0, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE959:
	.size	main, .-main
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB968:
	.cfi_startproc
	.cfi_personality 0x0,__gxx_personality_v0
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	cmpl	$1, 8(%ebp)
	jne	.L9
	cmpl	$65535, 12(%ebp)
	jne	.L9
	movl	$_ZStL8__ioinit, (%esp)
	call	_ZNSt8ios_base4InitC1Ev
	movl	$_ZNSt8ios_base4InitD1Ev, %eax
	movl	$__dso_handle, 8(%esp)
	movl	$_ZStL8__ioinit, 4(%esp)
	movl	%eax, (%esp)
	call	__cxa_atexit
.L9:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE968:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__I_main, @function
_GLOBAL__I_main:
.LFB969:
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
.LFE969:
	.size	_GLOBAL__I_main, .-_GLOBAL__I_main
	.section	.ctors,"aw",@progbits
	.align 4
	.long	_GLOBAL__I_main
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
