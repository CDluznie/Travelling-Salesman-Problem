#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include "map.hpp"
#include "path.hpp"

using namespace std;

class Solver {
	
public:	
	
	static Solver * create(const Map & map);
	
	void optimize();
	
	Path get_solution() const;

private :

	Solver(const Map & map, vector<Path> population);

	static int fitness(const Map & map, const Path & path);
	
	static Path cross_over(const Path & path1, const Path & path2);
	
	static void mutation(Path & path);

	Map map;
	
	vector<Path> population;
	
};

#endif
