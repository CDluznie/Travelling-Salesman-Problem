#include <iostream>
#include "map.hpp"
#include "path.hpp"
#include "solver.hpp"
#include "GPU_genetic_solver.hpp"
#include "drawer.hpp"
#include "SDL_drawer.hpp"

int main() {
	
	int number_cities = 150;
	int x_min = 100, x_max = 999;
	int y_min = 100, y_max = 999;
	
	Map map = Map::random(number_cities, x_min, x_max, y_min, y_max);
	
	int population_size = 128;
	float rate_path_crossover = 0.625;
	float rate_path_mutation = 0.85;
	GPU_genetic_solver * solver = GPU_genetic_solver::create(map, population_size, rate_path_crossover, rate_path_mutation);
	
	Path solution = solver->get_solution();
	
	Drawer * drawer = Drawer::new_SDL_drawer(900, 650, map, x_min, x_max, y_min, y_max);
	
	while (!drawer->stop()) {
		drawer->clean();
		drawer->draw_path(solution);
		drawer->update();
		solver->optimize();
		solution = solver->get_solution();
	}
	
	delete solver;
	delete drawer;
  
    return 0;
    
}


