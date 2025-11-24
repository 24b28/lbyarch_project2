section .data
var1 dq 255.0

section .text
bits 64
default rel
global imgCvtGrayIntToDouble

imgCvtGrayIntToDouble: ; n1@rcx, r2@rdx, pixels@r8, result@r9
	
	mov r10, rcx
	mov r11, rdx

	xor rcx, rcx

	row_loop:
		cmp rcx, r10
		jge end

		mov rsi, [r8+rcx*8]
		mov rdi, [r9+rcx*8]

		xor rbx, rbx
		jmp column_loop

	column_loop:
		cmp rbx, r11
		jge next_row

		cvtsi2sd xmm0, [rsi+rbx*4]
		divsd xmm0, [var1]
		movsd [rdi+rbx*8], xmm0

		inc rbx
		jmp column_loop

	next_row:
		inc rcx
		jmp row_loop

	end:
		mov rax, r9
		ret