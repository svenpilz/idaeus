#ifndef INCLUDE_GRAPHICS_PRIMITIVES_H
#define INCLUDE_GRAPHICS_PRIMITIVES_H

/**
 * @file
 * Defines frame buffer function to draw geometric primitives.
 */

#include <stdint.h>
#include <graphics/color.h>
#include <kernel/interfaces/framebuffer.h>

/**
 * Draw a solid colored line.
 *
 * @param fb Kernel frame buffer to use.
 * @param c Color of the line.
 * @param start_x x-coordinate of the first pixel.
 * @param start_y y-coordinate of the first pixel.
 * @param end_x x-coordinate of the last pixel.
 * @param end_y y-coordinate of the last pixel.
 */
void graphics_fb_draw_line(kernel_framebuffer_t* fb, color_t c,
	uint start_x, uint start_y, uint end_x, uint end_y);

/**
 * Draw the border of a rectangle.
 *
 * @param fb Kernel frame buffer to use.
 * @param c Color of the border.
 * @param start_x x-coordinate of the upper left corner.
 * @param start_y y-coordinate of the upper left corner.
 * @param end_x x-coordinate of the lower right corner.
 * @param end_y y-coordinate of the lower right corner.
 */
void graphics_fb_draw_rectangle(kernel_framebuffer_t* fb, color_t c,
	uint start_x, uint start_y, uint end_x, uint end_y);

/**
 * Draw a single colored one-pixel point.
 *
 * @param fb Kernel frame buffer to use.
 * @param c Color of the point.
 * @param x x-coordinate.
 * @param y y-coordinate.
 */
void graphics_fb_draw_point(kernel_framebuffer_t* fb, color_t c, uint x, uint y);

/**
 * Draw a colored rectangle without border. The coordinates
 * are inclusive.
 *
 * @param fb Kernel frame buffer to use.
 * @param c Color of the rectangle area.
 * @param start_x x-coordinate of the upper left corner.
 * @param start_y y-coordinate of the upper left corner.
 * @param end_x x-coordinate of the lower right corner.
 * @param end_y y-coordinate of the lower right corner.
 */
void graphics_fb_fill_rectangle(kernel_framebuffer_t* fb, color_t c,
	uint start_x, uint start_y, uint end_x, uint end_y);

#endif
