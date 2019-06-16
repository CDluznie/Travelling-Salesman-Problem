#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include "map.hpp"
#include "path.hpp"

using namespace std;

class Solver {
	
public:	
	
	explicit Solver(const Map & map);
	
	Path get_solution();

private :

	int distance(const Path & path) const; // TODO maybe remove

	Map map;
	Path path;

};

#endif
