#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include "map.hpp"
#include "path.hpp"

using namespace std;

class Solver {
	
public:	
	
	virtual ~Solver() {};
	
	virtual void optimize() = 0;
	
	virtual Path get_solution() const = 0;
	
	static Solver * new_genetic_solver(const Map * map, int population_size, float rate_path_crossover, float rate_path_mutation);

};

#endif
