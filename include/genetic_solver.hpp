#ifndef GENETIC_SOLVER_H
#define GENETIC_SOLVER_H

#include <vector>
#include "solver.hpp"
#include "map.hpp"
#include "path.hpp"

using namespace std;

class genetic_solver : public Solver {
	
public:	
	
	static genetic_solver * create(const Map & map, int population_size, float rate_path_crossover, float rate_path_mutation);
	
	void optimize() override;
	
	virtual Path get_solution() const override;

private :

	genetic_solver(const Map & map, vector<Path> population, int number_path_crossover, int number_path_mutation);

	static int fitness(const Map & map, const Path & path);

	static Path cross_over(const Path & path1, const Path & path2);

	static void mutation(Path & path);

	Map map;

	vector<Path> population;
	
	int number_path_crossover;
	
	int number_path_mutation;
	
};

#endif
