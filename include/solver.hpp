#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include "map.hpp"
#include "path.hpp"

using namespace std;

class Solver {
	
public:	
	
	explicit Solver(const Map & map);
	
	void optimize();
	
	Path get_solution() const;

private :

	int fitness(const Path & path) const; // TODO maybe remove
	
	void mutation(Path & path) const;

	Map map;
	
	vector<Path> population;

};

#endif
