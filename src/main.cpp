#include <iostream>
#include "map.hpp"
#include "path.hpp"
#include "solver.hpp"
#include "SDL_drawer.hpp"

int main() {
	
	int number_cities = 50;
	int x_min = 100, x_max = 999;
	int y_min = 100, y_max = 999;
	
	Map map = Map::random(number_cities, x_min, x_max, y_min, y_max);
	
	Path p1 = Path::random(map), p2 = Path::random(map);
	
	SDL_drawer drawer = SDL_drawer(900, 650);

	Solver solver(map);

	drawer.initialize(map, x_min, x_max, y_min, y_max);
	
	while (!drawer.stop()) {
		Path path = solver.get_solution();
		drawer.clean();
		drawer.draw_path(path);
		drawer.draw_map();
		solver.optimize();
	}
  
    return 0;
    
}


