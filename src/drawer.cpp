#include "drawer.hpp"
#include "SDL_drawer.hpp"

Drawer * Drawer::new_SDL_drawer(int window_width, int window_height, const Map & map) {
	return SDL_drawer::create(window_width, window_height, map);
}
