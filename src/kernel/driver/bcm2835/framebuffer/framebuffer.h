#ifndef KERNEL_DRIVER_BCM2835_FRAMEBUFFER_FRAMEBUFFER_H
#define KERNEL_DRIVER_BCM2835_FRAMEBUFFER_FRAMEBUFFER_H

#include <stdint.h>

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
} __attribute__((packed)) frame_buffer_info_t;

int framebuffer_init(frame_buffer_info_t* frame_buffer_info, uint32_t width, uint32_t height, uint32_t depth);

#endif
