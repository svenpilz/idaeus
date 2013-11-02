#include "framebuffer.h"
#include "mailbox.h"
#include <stdio.h>
#include <assert.h>

// The struct needs to be aligned for sending its pointer via mailbox.
bcm2835_framebuffer_info_t hardware_framebuffer __attribute__ ((aligned(16)));

int bcm2835_framebuffer_init(uint32_t width, uint32_t height, uint32_t depth) {
	hardware_framebuffer.physical_width = width;
	hardware_framebuffer.physical_height = height;
	hardware_framebuffer.virtual_width = width;
	hardware_framebuffer.virtual_height = height;
	hardware_framebuffer.gpu_pitch = 0;
	hardware_framebuffer.bit_depth = depth;
	hardware_framebuffer.x = 0;
	hardware_framebuffer.y = 0;
	hardware_framebuffer.gpu_pointer = 0;
	hardware_framebuffer.gpu_size = 0;
	
	mailbox_write(1, &hardware_framebuffer);
	
	/*
	 * Check status
	 */
	int status;
	
	if (mailbox_read(1, &status) != 0) {
		puts("[ERORR] bcm2835_framebuffer_init: failed to read form mail box.");
		return -1;
	} else if (status != 0) {
		puts("[ERORR] bcm2835_framebuffer_init: failed to set up.");
		return -2;
	} else if (hardware_framebuffer.gpu_pointer == 0) {
		puts("[ERORR] bcm2835_framebuffer_init: framebuffer at 0x0? Something is wrong here!");
		return -3;
	}
	
	printf("bcm2835 framebuffer: %ux%u (pixel depth=%u) at 0x%x (size=%u bytes).\n",
		hardware_framebuffer.physical_width,
		hardware_framebuffer.physical_height,
		hardware_framebuffer.bit_depth,
		hardware_framebuffer.gpu_pointer,
		hardware_framebuffer.gpu_size);
	
	return 0;
}

uint32_t* bcm2835_framebuffer_gpu_pointer() {
	return hardware_framebuffer.gpu_pointer;
}

int bcm2835_framebuffer_draw(const kernel_framebuffer_t* image) {
	if (image->height != hardware_framebuffer.virtual_height || 
		image->width != hardware_framebuffer.virtual_width || 
		image->depth != hardware_framebuffer.bit_depth) {
		return -1;
	}
	
	uint8_t* hw = (uint8_t*)hardware_framebuffer.gpu_pointer;
	uint8_t* img = image->frame;
	const uint32_t rows = hardware_framebuffer.virtual_height;
	const uint32_t cols = hardware_framebuffer.virtual_width;
	const uint8_t depth = hardware_framebuffer.bit_depth / 8;

	for (uint32_t row = 0; row < rows; ++row) {
		for (uint32_t col = 0; col < cols; ++col) {
			for (uint8_t i = 0; i < depth; i++) {
				*hw++ = *img++;
			}
		}
	}
	
	return 0;
}

