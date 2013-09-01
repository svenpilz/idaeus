#ifndef INCLUDE_GRAPHICS_COLOR_H
#define INCLUDE_GRAPHICS_COLOR_H

#include <stdint.h>

typedef uint32_t color_t;
typedef uint8_t color_component_t;

/*
 * Binary color format definition (BGR)
 */
static const uint32_t GRAPHICS_COLOR_COMPONENT_MASK_RED = 0xff;
static const uint32_t GRAPHICS_COLOR_COMPONENT_OFFSET_RED = 0;

static const uint32_t GRAPHICS_COLOR_COMPONENT_MASK_GREEN = 0xff00;
static const uint32_t GRAPHICS_COLOR_COMPONENT_OFFSET_GREEN = 8;

static const uint32_t GRAPHICS_COLOR_COMPONENT_MASK_BLUE = 0xff0000;
static const uint32_t GRAPHICS_COLOR_COMPONENT_OFFSET_BLUE = 16;

static const uint32_t GRAPHICS_COLOR_COMPONENT_MASK_ALPHA = 0xff000000;
static const uint32_t GRAPHICS_COLOR_COMPONENT_OFFSET_ALPHA = 24;

/*
 * Color constants.
 */
static const color_t GRAPHICS_COLOR_RED = 0xff;
static const color_t GRAPHICS_COLOR_GREEN = 0xff00;
static const color_t GRAPHICS_COLOR_BLUE = 0xff0000;

#define graphics_color_red(c) (color_t)((c & GRAPHICS_COLOR_COMPONENT_MASK_RED) >> GRAPHICS_COLOR_COMPONENT_OFFSET_RED)
#define graphics_color_green(c) (color_t)((c & GRAPHICS_COLOR_COMPONENT_MASK_GREEN) >> GRAPHICS_COLOR_COMPONENT_OFFSET_GREEN)
#define graphics_color_blue(c) (color_t)((c & GRAPHICS_COLOR_COMPONENT_MASK_BLUE) >> GRAPHICS_COLOR_COMPONENT_OFFSET_BLUE)
#define graphics_color_alpha(c) (color_t)((c & GRAPHICS_COLOR_COMPONENT_MASK_ALPHA) >> GRAPHICS_COLOR_COMPONENT_OFFSET_ALPHA)
#define graphics_color_set_red(c, red) (color_t)(c | ((color_t)red << GRAPHICS_COLOR_COMPONENT_OFFSET_RED))
#define graphics_color_set_green(c, green) (color_t)(c | ((color_t)green << GRAPHICS_COLOR_COMPONENT_OFFSET_GREEN))
#define graphics_color_set_blue(c, blue) (color_t)(c | ((color_t)blue << GRAPHICS_COLOR_COMPONENT_OFFSET_BLUE))
#define graphics_color_set_alpha(c, alpha) (color_t)(c | ((color_t)alpha << GRAPHICS_COLOR_COMPONENT_OFFSET_ALPHA))

color_t graphics_color(color_component_t red, color_component_t green,
	color_component_t blue, color_component_t alpha);

#endif
