#include <iostream>
#include "map.hpp"
#include "path.hpp"
#include "SDL_drawer.hpp"

int main() {
	
	
	SDL_drawer drawer = SDL_drawer(800, 650);
 
  
	Map map = Map::random(7,0,500,0,400);
	
	Path p1 = Path::random(map), p2 = Path::random(map);


	std::cout << map;
	std::cout << p1 << std::endl << p2 << std::endl;
  
	drawer.initialize();
	
	drawer.draw_map(map);
	drawer.draw_path(map, p1);
	
	drawer.wait_key();
	drawer.clean();
	
	drawer.draw_map(map);
	drawer.draw_path(map, p2);
	
	drawer.wait_key();
  
    return 0;
    
}


