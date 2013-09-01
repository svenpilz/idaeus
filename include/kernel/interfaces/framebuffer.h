#ifndef KERNEL_INTERFACES_FRAMEBUFFER_H
#define KERNEL_INTERFACES_FRAMEBUFFER_H

typedef struct {
	uint8_t* frame;
	uint8_t depth;
	uint32_t height;
	uint32_t width;
} kernel_framebuffer_t;

#endif
