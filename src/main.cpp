#include <iostream>
#include "map.hpp"
#include "path.hpp"
#include "genetic_solver.hpp"
#include "drawer.hpp"
#include "SDL_drawer.hpp"
#include <tclap/CmdLine.h>

Path solve_travelling_salesman(Solver * solver, Drawer * drawer) {
	Path solution = solver->get_solution();
	while (!drawer->stop()) {
		drawer->clean();
		drawer->draw_path(solution);
		drawer->update();
		solver->optimize();
		solution = solver->get_solution();
	}
	return solution;
}

int main(int argc, char** argv) {
	
	int random_x_min = 100, random_x_max = 999;
	int random_y_min = 100, random_y_max = 999;
	
	int population_size = 128;
	float rate_path_crossover = 0.625;
	float rate_path_mutation = 0.85;
	
	int window_width = 950;
	int window_height = 650;
	
	string map_input_file_name;
	string path_output_file_name;
	int number_cities;
	bool random;
	
	try {

		TCLAP::CmdLine cmd("Travelling salesman problem solver", ' ', "1.0");
		
		TCLAP::ValueArg<string> output_arg("o", "output", "Output file name for the solution path", true, "", "path");
		TCLAP::ValueArg<int> random_arg("r", "random", "Solve the problem on a random map with the specified number of cities", true, 0, "int");
		TCLAP::ValueArg<string> input_arg("f", "file", "Solve the problem on the JSON representation of the specified map", true, "", "path");
		
		cmd.add(output_arg);
		cmd.xorAdd(random_arg, input_arg);
		
		cmd.parse(argc, argv);
		
		map_input_file_name = input_arg.getValue();
		path_output_file_name = output_arg.getValue();
		number_cities = random_arg.getValue();
		random = (map_input_file_name == "");

    } catch (TCLAP::ArgException &e) { 
		cerr << "error: " << e.error() << " for arg " << e.argId() << endl;
		return 1;
	}

	Map * map = nullptr;
	
	if (random) {
		
		if (number_cities < 4) {
			cerr << "error: the number of cities should be greater than 3 " << endl;
			return 1;
		}
		
		map = Map::random(number_cities, random_x_min, random_x_max, random_y_min, random_y_max);

	} else {
	
		map = Map::read_JSON_file(map_input_file_name);
	
	}
	
	Solver * solver = Solver::new_genetic_solver(map, population_size, rate_path_crossover, rate_path_mutation);
	
	Drawer * drawer = Drawer::new_SDL_drawer(window_width, window_height, *map);
	
	Path solution = solve_travelling_salesman(solver, drawer);
	
	cout << "write solution in " << path_output_file_name << endl;
	solution.write_JSON_file(path_output_file_name);
	
	delete map;
	delete solver;
	delete drawer;
  
    return 0;
    
}


