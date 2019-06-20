#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include "map.hpp"
#include "path.hpp"

using namespace std;

class Solver {
	
public:	
	
	//TODO factory
	
	virtual ~Solver() {};
	
	virtual void optimize() = 0;
	
	virtual Path get_solution() const = 0;

};

#endif
