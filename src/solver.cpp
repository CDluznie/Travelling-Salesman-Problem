#include "solver.hpp"

Solver::Solver(const Map & map) : map(map), path(Path::random(map)) {

}

Path Solver::get_solution() const {
	return Path::random(map);
}
