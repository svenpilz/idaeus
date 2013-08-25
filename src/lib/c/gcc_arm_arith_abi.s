@
@ {unsigned int quotient, unsigned int remainder}
@ __aeabi_uidivmod(unsigned int dividend, unsigned int numerator)
@
@ unsigned integer division and remainder
@ 
@ This function could not be implemented in C, because it returns
@ two values via registers (r0 and r1).
@
.global __aeabi_uidivmod
__aeabi_uidivmod:
	push {lr}
	push {r0}
	push {r1}
	
	bl __aeabi_uidiv

	pop {r2}
	mul r1, r0, r2

	pop {r2}
	rsb r1, r1, r2
	
	pop {lr}
	bx lr

