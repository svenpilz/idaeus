#ifndef KERNEL_INTERFACES_FRAMEBUFFER_H
#define KERNEL_INTERFACES_FRAMEBUFFER_H

typedef struct {
	/**
	 * Pointer to the actual frame buffer.
	 */
	uint8_t* frame;
	
	/**
	 * Number of bits per pixel.
	 */
	uint8_t depth;
	
	/**
	 * Number of rows.
	 */
	uint32_t height;
	
	/**
	 * Number of pixels per row.
	 */
	uint32_t width;
} kernel_framebuffer_t;

#endif
