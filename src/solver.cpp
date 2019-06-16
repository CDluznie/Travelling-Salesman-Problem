#include "solver.hpp"
#include <algorithm>
#include <random>

Solver::Solver(const Map & map) : map(map), population() {
	int population_size = 100;
	for (int i = 0; i < population_size; i++) {
		population.push_back(Path::random(map));
	}
}

int Solver::fitness(const Path & path) const {
	int d = 0;
	for (int i = 0; i < path.number_cities()-1; i++) {
		d += map[path[i]].distance(map[path[i+1]]);
	}
	return d;
}

void Solver::mutation(Path & path) const {
	mt19937 generator(random_device{}());
	uniform_int_distribution<int> dist(1,path.number_cities()-2);
	int i = dist(generator);
	swap(path[i], path[i+1]);
}

void Solver::optimize() {
	vector<Path> childs_population(population);
	for_each(childs_population.begin(), childs_population.end(), [this](Path & p) {
		mutation(p);
	});
	population.insert(population.end(), childs_population.begin(), childs_population.end());
	sort(population.begin(), population.end(), [this](const Path & p1, const Path & p2) {
		return fitness(p1) < fitness(p2);
	});
	population = vector<Path>(population.begin(), population.begin() + 100);
}

Path Solver::get_solution() const {
	return population[0];
}
