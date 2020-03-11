.section ".text.boot"

// Boot entry function
.globl _start
_start:
	mov sp, #0x8000

	// Clear bss section
	ldr r4, =__bss_start
	ldr r9, =__bss_end
	mov r5, #0
	mov r6, #0
	mov r7, #0
	mov r8, #0
	b 2f

1:
	stmia r4!, {r5-r8}
2:
	cmp r4, r9
	blo 1b

	blx kernel_main
halt:
	b halt
