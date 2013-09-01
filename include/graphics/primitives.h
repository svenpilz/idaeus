#ifndef INCLUDE_GRAPHICS_PRIMITIVES_H
#define INCLUDE_GRAPHICS_PRIMITIVES_H

#include <stdint.h>
#include "../../src/kernel/interfaces/framebuffer.h"

void graphics_fb_draw_line(kernel_framebuffer_t* fb, uint start_x, uint start_y, uint end_x, uint end_y);
void graphics_fb_point(kernel_framebuffer_t* fb, uint x, uint y);

#endif
