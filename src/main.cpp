#include <iostream>
#include "map.hpp"
#include "path.hpp"
#include "solver.hpp"
#include "SDL_drawer.hpp"

int main() {
	
	int number_cities = 75;
	int x_min = 100, x_max = 999;
	int y_min = 100, y_max = 999;
	
	Map map = Map::random(number_cities, x_min, x_max, y_min, y_max);
	
	Solver solver(map);
	
	Path solution = solver.get_solution();
	
	SDL_drawer drawer = SDL_drawer(900, 650);

	drawer.initialize(map, x_min, x_max, y_min, y_max);
	
	while (!drawer.stop()) {
		Path path = solver.get_solution();
		drawer.clean();
		drawer.draw_path(path);
		drawer.update();
		solver.optimize();
	}
  
    return 0;
    
}


