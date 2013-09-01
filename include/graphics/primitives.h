#ifndef INCLUDE_GRAPHICS_PRIMITIVES_H
#define INCLUDE_GRAPHICS_PRIMITIVES_H

#include <stdint.h>
#include <graphics/color.h>
#include <kernel/interfaces/framebuffer.h>

void graphics_fb_draw_line(kernel_framebuffer_t* fb, color_t c,
	uint start_x, uint start_y, uint end_x, uint end_y);
	
void graphics_fb_draw_rectangle(kernel_framebuffer_t* fb, color_t c,
	uint start_x, uint start_y, uint end_x, uint end_y);
	
void graphics_fb_draw_point(kernel_framebuffer_t* fb, color_t c, uint x, uint y);

void graphics_fb_fill_rectangle(kernel_framebuffer_t* fb, color_t c,
	uint start_x, uint start_y, uint end_x, uint end_y);

#endif
