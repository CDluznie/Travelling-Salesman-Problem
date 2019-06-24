#include <iostream>
#include "map.hpp"
#include "path.hpp"
#include "genetic_solver.hpp"
#include "drawer.hpp"
#include "SDL_drawer.hpp"

Path solve_travelling_salesman(Solver * solver, Drawer * drawer) {
	Path solution = solver->get_solution();
	while (!drawer->stop()) {
		drawer->clean();
		drawer->draw_path(solution);
		drawer->draw_stats(solution);
		drawer->update();
		solver->optimize();
		solution = solver->get_solution();
	}
	return solution;
}

int main() {
	
	/*
	json jsonFigure;
	ifstream fichierFigure(fichier);
	fichierFigure >> jsonFigure;
	fichierFigure.close();
	*/
	
	bool random = false;

	Map * map = nullptr;
	
	if (random) {
		
		int x_min = 100, x_max = 999;
		int y_min = 100, y_max = 999;
		
		int number_cities = 150;
		
		map = new Map(Map::random(number_cities, x_min, x_max, y_min, y_max));

	} else {
	
		map = new Map(Map::read_JSON_file("data/map.json"));
	
	}
	
	int population_size = 128;
	float rate_path_crossover = 0.625;
	float rate_path_mutation = 0.85;
	Solver * solver = Solver::new_genetic_solver(map, population_size, rate_path_crossover, rate_path_mutation);
	
	Drawer * drawer = Drawer::new_SDL_drawer(900, 650, *map);
	
	Path solution = solve_travelling_salesman(solver, drawer);
	
	delete map;
	delete solver;
	delete drawer;
  
    return 0;
    
}


