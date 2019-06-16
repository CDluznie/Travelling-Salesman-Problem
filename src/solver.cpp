#include "solver.hpp"
#include <algorithm>
#include <random>


#include <random>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <map>

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

Path Solver::cross_over(const Path & path1, const Path & path2) const {
	int n = path1.number_cities();
	std::map<int, int> positions;
	for (int i = 0; i < n; i++) { // TODO extremities
		positions[path2[i]] = i;
	}
	mt19937 generator(random_device{}());
	int begin = uniform_int_distribution<int>(1, n-2)(generator);
	int end = uniform_int_distribution<int>(begin, n-2)(generator);
	for (int i = begin; i <= end; i++) {
		swap(positions[path1[i]], positions[i]);
	}
	vector<int> child(n);
	for (int i = 0; i < n; i++) {
		child[positions[i]] = i;
	}
	return Path(child);
}

void Solver::mutation(Path & path) const {
	mt19937 generator(random_device{}());
	int n = path.number_cities();
	int l = uniform_int_distribution<int>(1, (n-2)/2)(generator); //TODO extremities
	int i = uniform_int_distribution<int>(1, n-2*l-1)(generator); //TODO extremities
	int j = uniform_int_distribution<int>(i+l, n-l-1)(generator); //TODO extremities
	for (int k = 0; k < l; k++) {
		swap(path[i+k], path[j+k]);
	}
}

void Solver::optimize() {
	int n = 10;
	
	
	vector<Path> childs_population;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			childs_population.push_back(cross_over(population[i], population[j]));
		}
		for (int j = i+1; j < n; j++) {
			childs_population.push_back(cross_over(population[i], population[j]));
		}
	}
	for_each(childs_population.begin(), childs_population.end(), [this](Path & p) {
		mutation(p);
	});
	population.insert(population.end(), childs_population.begin(), childs_population.end());
	sort(population.begin(), population.end(), [this](const Path & p1, const Path & p2) {
		return fitness(p1) < fitness(p2);
	});
	population = vector<Path>(population.begin(), population.begin() + 100); // TODO avoid copy
}

Path Solver::get_solution() const {
	return population[0];
}
