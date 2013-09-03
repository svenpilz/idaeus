#ifndef KERNEL_PLATFORM_BCM2835_FRAMEBUFFER_H
#define KERNEL_PLATFORM_BCM2835_FRAMEBUFFER_H

#include <stdint.h>
#include <kernel/interfaces/framebuffer.h>

typedef struct {
	uint32_t physical_width;
	uint32_t physical_height;
	uint32_t virtual_width;
	uint32_t virtual_height;
	uint32_t gpu_pitch;
	uint32_t bit_depth;
	uint32_t x;
	uint32_t y;
	uint32_t gpu_pointer;
	uint32_t gpu_size;
} __attribute__((packed)) bcm2835_framebuffer_info_t;

int bcm2835_framebuffer_init(uint32_t width, uint32_t height, uint32_t depth);
int bcm2835_framebuffer_draw(const kernel_framebuffer_t* image);

#endif
