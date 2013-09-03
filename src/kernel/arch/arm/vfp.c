#include "vfp.h"
#include <stdint.h>

const uint32_t ARM_FPU_FPEXC_FLAG_ENABLE = 1 << 30;

uint32_t arm_fpu_read_fpexc() {
	uint32_t v;
	asm("vmrs %0, fpexc" : "=r" (v));
	return v;
}

void arm_fpu_set_fpexc(uint32_t v) {
	asm("vmsr fpexc, %0" : : "r" (v));
}

int arm_vfp_init() {
	arm_fpu_set_fpexc(arm_fpu_read_fpexc() | ARM_FPU_FPEXC_FLAG_ENABLE);
}
