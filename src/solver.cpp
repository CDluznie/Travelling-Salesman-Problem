#include "solver.hpp"
#include <algorithm>
#include <random>
#include <set>
#include <queue>

Solver::Solver(const Map & map, vector<Path> population, int number_path_crossover, int number_path_mutation) :
	map(map),
	population(population),
	number_path_crossover(number_path_crossover),
	number_path_mutation(number_path_mutation) {

}

Solver * Solver::create(const Map & map) {
	vector<Path> population;
	
	int population_size = 128;
	float rate_path_crossover = 0.625;
	float rate_path_mutation = 0.85;
	
	
	for (int i = 0; i < population_size; i++) {
		population.push_back(Path::random(map));
	}
	sort(population.begin(), population.end(), [&map](const Path & p1, const Path & p2) {
		return fitness(map, p1) < fitness(map, p2);
	});
	return new Solver(map, population, population_size*rate_path_crossover, population_size*rate_path_mutation);
}

int Solver::fitness(const Map & map, const Path & path) {
	int d = 0;
	for (int i = 0; i < path.number_cities()-1; i++) {
		d += map[path[i]].distance(map[path[i+1]]);
	}
	return d;
}

Path Solver::cross_over(const Path & path1, const Path & path2) {
	mt19937 generator(random_device{}());
	int n = path1.number_cities();
	
	
	/* */
	Path path = Path(vector<int>(n));
	int i = uniform_int_distribution<int>(1, n-3)(generator);
	int j = uniform_int_distribution<int>(i+1, n-2)(generator);
	
	set<int> seen;
	for (int k = i; k <= j; k++) {
		path[k] = path1[i];
		seen.insert(path1[i]);
	}
	queue<int> not_seen;
	for (int k = 0; k < n; k++) {
		if (seen.find(path2[k]) == seen.end()) {
			not_seen.push(path2[k]);
		}
	}
	
	for (int k = 0; k < i; k++) {
		path[k] = not_seen.front();
		not_seen.pop();
	}
	for (int k = i+1; k < n; k++) {
		path[k] = not_seen.front();
		not_seen.pop();
	}
	
	/* */
	
	
	/*
	Path path = Path(vector<int>(n));
	int i = uniform_int_distribution<int>(1, n-2)(generator);
	int first = path1[i];
	int previous = path2[i];
	path[i] = path1[i];
	while (previous != first) {
		if (path1[i] == previous) {
			path[i] = path1[i];
			previous = path2[i];
		}
		i = (i+1)%n;
	}
	for (i = 0 ; i < n ; i++) {
		if (path[i] == 0) {
			path[i] = path2[i];
		}
    }
	*/

	return path;
}

void Solver::mutation(Path & path) {
	// 2-OPT mutation
	mt19937 generator(random_device{}());
	int n = path.number_cities();
	int i = uniform_int_distribution<int>(1, n-3)(generator);
	int j = uniform_int_distribution<int>(i+1, n-2)(generator);
	while (i < j) {
		swap(path[i], path[j]);
		i++;
		j--;
	}
}

void Solver::optimize() {
	vector<Path> childs_population;
	for (unsigned int i = 0; i <  population.size(); i++) {
		childs_population.push_back(cross_over(population[(2*i) % number_path_crossover], population[(2*i + 1) % number_path_crossover]));
	}
	for_each(childs_population.begin(), childs_population.begin()+number_path_mutation, [](Path & p) {
		mutation(p);
	});
	sort(childs_population.begin(), childs_population.end(), [this](const Path & p1, const Path & p2) {
		return fitness(this->map, p1) < fitness(this->map, p2);
	});
	vector<Path> next_population;
	int parent_index = 0;
	int child_index = 0;
	for (unsigned int i = 0; i <  population.size(); i++) {
		if (fitness(map, population[parent_index]) < fitness(map, childs_population[child_index])) {
			next_population.push_back(population[parent_index++]);
		} else {
			next_population.push_back(childs_population[child_index++]);
		}
	}
	population = next_population;
}

Path Solver::get_solution() const {
	return population[0];
}
