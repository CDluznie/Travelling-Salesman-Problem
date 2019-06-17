#include "drawer.hpp"
#include "SDL_drawer.hpp"

Drawer * Drawer::new_SDL_drawer(int window_width, int window_height, const Map & map, int x_min, int x_max, int y_min, int y_max) {
	return SDL_drawer::create(window_width, window_height, map, x_min, x_max, y_min, y_max);
}
