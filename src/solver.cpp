#include "solver.hpp"

Solver::Solver(const Map & map) : map(map), path(Path::random(map)) {

}

int Solver::distance(const Path & path) const {
	int d = 0;
	for (int i = 0; i < path.number_cities()-1; i++) {
		d += map[path[i]].distance(map[path[i+1]]);
	}
	return d;
}

Path Solver::get_solution() {
	Path current = Path::random(map);
	if (distance(current) < distance(path)) {
		path = current;
	}
	return path;
}
