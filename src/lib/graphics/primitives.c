#include <primitives.h>
#include <stdio.h>

/**
 * @param fb Pointer to the frame buffer.
 * @param u Column of the pixel (left to right).
 * @param v Row of the Pixel (top to bottom).
 * @return Pointer to the first (color-) component of the pixel.
 */
uint8_t* kernel_framebuffer_pixel(kernel_framebuffer_t* fb, uint32_t u, uint32_t v) {
	return fb->frame + (u * fb->width * (fb->depth/8) + v * (fb->depth/8));
}

void graphics_fb_draw_line(kernel_framebuffer_t* fb, uint start_x, uint start_y, uint end_x, uint end_y) {
	int diff_x = end_x - start_x;
	int diff_y = end_y - start_y;
	int offset_x = diff_x < 0 ? -1 : 1;
	int offset_y = diff_y < 0 ? -1 : 1;
	uint x = start_x;
	uint y = start_y;
	float error = 0;
	float delta_error = (float)(start_y - end_y) / (float)(start_x - end_x);
	
	if (delta_error < 0) {
		delta_error *= -1;
	}
	
	while (x != end_x + offset_x) {
		uint8_t* p = kernel_framebuffer_pixel(fb, x, y);
		*p++ = 0;
		*p++ = 255;
		*p++ = 0;
		
		x += offset_x;
		error += delta_error;
		
		if (delta_error >= 0.5) {
			y += offset_y;
			error = 0;
		}
	}
}

void graphics_fb_point(kernel_framebuffer_t* fb, uint x, uint y) {
	uint8_t* p = kernel_framebuffer_pixel(fb, x, y);
		*p++ = 0;
		*p++ = 255;
		*p++ = 0;
}
