/*
 * ARMadillo/kernel/lock.S
 *
 * Provides some lock functionality.
 *
 */

.section ".text"

.globl try_lock
@ Takes a pointer to a lock variable and uses atomic operations to aqcuire the lock.
@ Returns 0 if the lock was not acquired, 1 if it was.
try_lock:
	mov     r1, #0
	swp     r2, r1, [r0]    @ stores the value in r1 into the address in r0,
				@ and stores the value at the address in r0 into r2
	mov     r0, r2
	blx     lr
