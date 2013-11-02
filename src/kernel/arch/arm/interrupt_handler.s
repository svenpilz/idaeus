.section .text

.global arm_interrupt_entry_reset
.global arm_interrupt_entry_undefined
.global arm_interrupt_entry_swi
.global arm_interrupt_entry_prefetch_abort
.global arm_interrupt_entry_data_abort
.global arm_interrupt_entry_unused
.global arm_interrupt_entry_irq
.global arm_interrupt_entry_fiq

.macro SAVE_REGISTER_SET
	sub lr, lr, #4
	push {lr}            @ save last user pc
	stmdb sp!, {r0-lr}^  @ save user registers
	mrs r0, spsr
	push {r0}
	@vpush {d0-d15}       @ save fpu registers
.endm

.macro CALL_HANDLER
	mov r1, sp
	bl arm_handle_interrupt
.endm

.macro RESTORE_REGISTER_SET
	mov sp, r0        @ context to restore
	@vpop {d0-d15}     @ restore fpu registers
	pop {r0}          @ restore user register
	msr spsr_cxsf, r0
	ldm sp!, {r0-lr}^ 
	ldm sp!, {pc}^    @ switch context
.endm

arm_interrupt_entry_reset:
	SAVE_REGISTER_SET
	mov r0, #0
	CALL_HANDLER
	RESTORE_REGISTER_SET
	
arm_interrupt_entry_undefined:
	SAVE_REGISTER_SET
	mov r0, #1
	CALL_HANDLER
	RESTORE_REGISTER_SET
	
arm_interrupt_entry_swi:
	SAVE_REGISTER_SET
	mov r0, #2
	CALL_HANDLER
	RESTORE_REGISTER_SET
	
arm_interrupt_entry_prefetch_abort:
	SAVE_REGISTER_SET
	mov r0, #3
	CALL_HANDLER
	RESTORE_REGISTER_SET
	
arm_interrupt_entry_data_abort:
	SAVE_REGISTER_SET
	mov r0, #4
	CALL_HANDLER
	RESTORE_REGISTER_SET
	
arm_interrupt_entry_unused:
	SAVE_REGISTER_SET
	mov r0, #5
	CALL_HANDLER
	RESTORE_REGISTER_SET
	
arm_interrupt_entry_irq:
	SAVE_REGISTER_SET
	mov r0, #6
	CALL_HANDLER
	RESTORE_REGISTER_SET
	
arm_interrupt_entry_fiq:
	SAVE_REGISTER_SET
	mov r0, #7
	CALL_HANDLER
	RESTORE_REGISTER_SET

