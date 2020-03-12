.section ".text"

// Helper functions
// GET32 function
// arg0 = [arg0]
.globl GET32
GET32:
	ldr r0, [r0]
	bx lr

// PUT32 function
// [arg0] = arg1
.globl PUT32
PUT32:
	str r1, [r0]
	bx lr
