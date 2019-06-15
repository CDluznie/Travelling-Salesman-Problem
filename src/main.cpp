#include <iostream>
#include "map.hpp"
#include "path.hpp"
#include "SDL_drawer.hpp"

int main() {
	
	Map map = Map::random(7, 100, 999, 100, 999);
	
	Path p1 = Path::random(map), p2 = Path::random(map);
	
	SDL_drawer drawer = SDL_drawer(900, 650);

	drawer.initialize(&map);
	
	drawer.draw_map();
	drawer.draw_path(p1);
	
	drawer.wait_key();
	drawer.clean();
	
	drawer.draw_map();
	drawer.draw_path(p2);
	
	drawer.wait_key();
  
    return 0;
    
}


