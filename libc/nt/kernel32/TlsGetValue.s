.include "o/libc/nt/codegen.inc"
.imp	kernel32,__imp_TlsGetValue,TlsGetValue,0

	.text.windows
__TlsGetValue:
	push	%rbp
	mov	%rsp,%rbp
	.profilable
	mov	%rdi,%rcx
	sub	$32,%rsp
	call	*__imp_TlsGetValue(%rip)
	leave
	ret
	.endfn	__TlsGetValue,globl
	.previous
