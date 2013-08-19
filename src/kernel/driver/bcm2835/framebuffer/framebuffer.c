#include "framebuffer.h"
#include "../mailbox/mailbox.h"

#include <stdio.h>

int framebuffer_init(frame_buffer_info_t* frame_buffer_info, uint32_t width, uint32_t height, uint32_t depth) {
	frame_buffer_info->physical_width = 1024;
	frame_buffer_info->physical_height = 768;
	frame_buffer_info->virtual_width = 1024;
	frame_buffer_info->virtual_height = 768;
	frame_buffer_info->gpu_pitch = 0;
	frame_buffer_info->bit_depth = 16;
	frame_buffer_info->x = 0;
	frame_buffer_info->y = 0;
	frame_buffer_info->gpu_pointer = 0;
	frame_buffer_info->gpu_size = 0;
	
	mailbox_write(1, frame_buffer_info);
	
	/*
	 * Check status
	 */
	int status;
	
	if (mailbox_read(1, &status) != 0) {
		puts("[ERORR] framebuffer_init: failed to read form mail box.");
		return -1;
	} else if (status != 0) {
		puts("[ERORR] framebuffer_init: failed to set up.");
		return -2;
	}
	
	return 0;
}
