#include <graphics/color.h>

color_t graphics_color(color_component_t red, color_component_t green,
	color_component_t blue, color_component_t alpha) {
	return graphics_color_set_red(
		graphics_color_set_green(
			graphics_color_set_blue(
				graphics_color_set_alpha(0, alpha),
				blue),
			green),
		red);
}

