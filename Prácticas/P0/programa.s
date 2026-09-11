	.arch armv8-a
	.file	"programa.c"
	.text
	.section	.rodata
	.align	3
.LC0:
	.string	"Hola Mundo !"
	.align	3
.LC1:
	.string	"Resultado : %f\n"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
.LFB6:
	.cfi_startproc
	stp	x29, x30, [sp, -32]!
	.cfi_def_cfa_offset 32
	.cfi_offset 29, -32
	.cfi_offset 30, -24
	mov	x29, sp
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	bl	puts
	mov	w0, 12793
	movk	w0, 0x41e2, lsl 16
	fmov	s31, w0
	str	s31, [sp, 28]
	ldr	s31, [sp, 28]
	fcvt	d31, s31
	fmov	d0, d31
	adrp	x0, .LC1
	add	x0, x0, :lo12:.LC1
	bl	printf
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.ident	"GCC: (GNU) 14.1.1 20240701 (Red Hat 14.1.1-7)"
	.section	.note.GNU-stack,"",@progbits
