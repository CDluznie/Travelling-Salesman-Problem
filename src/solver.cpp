#include "solver.hpp"
#include "genetic_solver.hpp"

Solver * Solver::new_genetic_solver(const Map & map, int population_size, float rate_path_crossover, float rate_path_mutation) {
	return genetic_solver::create(map, population_size, rate_path_crossover, rate_path_mutation);
}
