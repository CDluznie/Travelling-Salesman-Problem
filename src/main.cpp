#include <iostream>
#include "map.hpp"
#include "path.hpp"
#include "SDL_drawer.hpp"

int main() {
	
	int number_cities = 100;
	int x_min = 100, x_max = 999;
	int y_min = 100, y_max = 999;
	
	Map map = Map::random(number_cities, x_min, x_max, y_min, y_max);
	
	Path p1 = Path::random(map), p2 = Path::random(map);
	
	SDL_drawer drawer = SDL_drawer(900, 650);

	drawer.initialize(map, x_min, x_max, y_min, y_max);
	
	while (!drawer.stop()) {
		drawer.draw_map();
		
		//drawer.wait_key();
		drawer.clean();
		
		drawer.draw_path(p1);
		drawer.draw_map();
		
		//drawer.wait_key();
		drawer.clean();
		
		drawer.draw_path(p2);
		drawer.draw_map();
	
		//drawer.wait_key();
	}
	
	cout << "fin" << endl;
  
    return 0;
    
}


