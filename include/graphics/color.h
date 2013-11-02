#ifndef INCLUDE_GRAPHICS_COLOR_H
#define INCLUDE_GRAPHICS_COLOR_H

/**
 * @file
 * Defines functions and constants for RGBA color handling, the information
 * is internally stored as ABGR. The functions for getting and setting
 * color components are implemented as macros, as they may be used
 * in loops or performance critical code paths.
 */

#include <stdint.h>

/**
 * Stores RGB color information with alpha channel.
 */
typedef uint32_t color_t;

/**
 * Stores one RGBA component.
 */
typedef uint8_t color_component_t;

/*
 * Binary color format definition (ABGR)
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
static const color_t GRAPHICS_COLOR_WHITE = 0xffffff;
static const color_t GRAPHICS_COLOR_BLACK = 0x000000;

/**
 * Extract the red color compoment of @ref color_t.
 * @param c Color (@ref color_t)
 * @return @ref color_component_t
 */
#define graphics_color_red(c) (color_component_t)((c & GRAPHICS_COLOR_COMPONENT_MASK_RED) >> GRAPHICS_COLOR_COMPONENT_OFFSET_RED)

/**
 * Extract the green color compoment of @ref color_t.
 * @param c Color (@ref color_t)
 * @return @ref color_component_t
 */
#define graphics_color_green(c) (color_component_t)((c & GRAPHICS_COLOR_COMPONENT_MASK_GREEN) >> GRAPHICS_COLOR_COMPONENT_OFFSET_GREEN)

/**
 * Extract the blue color compoment of @ref color_t.
 * @param c Color (@ref color_t)
 * @return @ref color_component_t
 */
#define graphics_color_blue(c) (color_component_t)((c & GRAPHICS_COLOR_COMPONENT_MASK_BLUE) >> GRAPHICS_COLOR_COMPONENT_OFFSET_BLUE)

/**
 * Extract the alpha channel of @ref color_t.
 * @param c Color (@ref color_t)
 * @return @ref color_component_t
 */
#define graphics_color_alpha(c) (color_component_t)((c & GRAPHICS_COLOR_COMPONENT_MASK_ALPHA) >> GRAPHICS_COLOR_COMPONENT_OFFSET_ALPHA)

/**
 * Set the red color component of @ref color_t. The parameters are read-only,
 * a new @ref color_t is returned.
 * @param c Color (@ref color_t)
 * @param red Component (@ref color_component_t)
 * @return The new color (@ref color_t)
 */
#define graphics_color_set_red(c, red) (color_t)(c | ((color_t)red << GRAPHICS_COLOR_COMPONENT_OFFSET_RED))

/**
 * Set the green color component of @ref color_t. The parameters are read-only,
 * a new @ref color_t is returned.
 * @param c Color (@ref color_t)
 * @param green Component (@ref color_component_t)
 * @return The new color (@ref color_t)
 */
#define graphics_color_set_green(c, green) (color_t)(c | ((color_t)green << GRAPHICS_COLOR_COMPONENT_OFFSET_GREEN))

/**
 * Set the blue color component of @ref color_t. The parameters are read-only,
 * a new @ref color_t is returned.
 * @param c Color (@ref color_t)
 * @param blue Component (@ref color_component_t)
 * @return The new color (@ref color_t)
 */
#define graphics_color_set_blue(c, blue) (color_t)(c | ((color_t)blue << GRAPHICS_COLOR_COMPONENT_OFFSET_BLUE))

/**
 * Set the alpha channel of @ref color_t. The parameters are read-only,
 * a new @ref color_t is returned.
 * @param c Color (@ref color_t)
 * @param alpha Alpha channel (@ref color_component_t)
 * @return The new color (@ref color_t)
 */
#define graphics_color_set_alpha(c, alpha) (color_t)(c | ((color_t)alpha << GRAPHICS_COLOR_COMPONENT_OFFSET_ALPHA))

/**
 * Helper function to create a @ref color_t from its components.
 */
color_t graphics_color(color_component_t red, color_component_t green,
	color_component_t blue, color_component_t alpha);

#endif
