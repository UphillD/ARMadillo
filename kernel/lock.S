/*
 * ARMadillo/kernel/lock.S
 *
 * Provides some lock functionality.
 */

.section ".text"

@ Takes a pointer to a lock variable and uses atomic operations
@  to acquire the lock.
@ Returns 0 if the lock was not acquired, 1 if it was.
.globl lock_try
lock_try:
	mov	r1, #0
	swp	r2, r1, [r0]    @ [r0] =  r1
				@  r2  = [r0]
	mov	r0, r2
	blx	lr
