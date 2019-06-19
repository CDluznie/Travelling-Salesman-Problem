#ifndef GPU_GENETIC_SOLVER_H
#define GPU_GENETIC_SOLVER_H

#include <vector>
#include "map.hpp"
#include "path.hpp"

using namespace std;

class GPU_genetic_solver {
	
public:	
	
	static GPU_genetic_solver * create(const Map & map, int population_size, float rate_path_crossover, float rate_path_mutation);
	
	~GPU_genetic_solver();
	
	void optimize();
	
	Path get_solution() const;

private :

	GPU_genetic_solver(int2 *dev_map, int map_size, int *dev_population, int *dev_childs_population, int population_size, int number_path_crossover, int number_path_mutation);

	static int fitness(const Map & map, const Path & path);

	static Path cross_over_tmp(const Path & path1, const Path & path2);

	static void mutation_tmp(Path & path);

	int2 *dev_map;

	int map_size;

	int *dev_population;
	
	int *dev_childs_population;

	int population_size;
	
	int number_path_crossover;
	
	int number_path_mutation;
	
	
};

#endif
