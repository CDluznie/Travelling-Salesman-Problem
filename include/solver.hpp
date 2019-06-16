#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include "map.hpp"
#include "path.hpp"

using namespace std;

class Solver {
	
public:	
	
	explicit Solver(const Map & map);
	
	Path get_solution() const;

private :

	Map map;
	Path path;

};

#endif
