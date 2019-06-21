#include "genetic_solver.hpp"
#include <algorithm>
#include <random>
#include <set>
#include <queue>

genetic_solver::genetic_solver(const Map & map, vector<Path> population, int number_path_crossover, int number_path_mutation) :
	map(map),
	population(population),
	number_path_crossover(number_path_crossover),
	number_path_mutation(number_path_mutation) {

}

genetic_solver * genetic_solver::create(const Map & map, int population_size, float rate_path_crossover, float rate_path_mutation) {
	vector<Path> population;
	for (int i = 0; i < population_size; i++) {
		population.push_back(Path::random(map));
	}
	sort(population.begin(), population.end(), [&map](const Path & p1, const Path & p2) {
		return fitness(map, p1) < fitness(map, p2);
	});
	return new genetic_solver(map, population, population_size*rate_path_crossover, population_size*rate_path_mutation);
}

int genetic_solver::fitness(const Map & map, const Path & path) {
	int d = 0;
	for (int i = 0; i < path.number_cities()-1; i++) {
		d += map[path[i]].distance(map[path[i+1]]);
	}
	return d;
}

Path genetic_solver::cross_over(const Path & path1, const Path & path2) {
	mt19937 generator(random_device{}());
	int n = path1.number_cities();
	
	
	/* */
	// OX crossover
	Path path = Path(vector<int>(n));
	int i = uniform_int_distribution<int>(1, n-3)(generator);
	int j = uniform_int_distribution<int>(i+1, n-2)(generator);
	set<int> seen;
	for (int k = i; k <= j; k++) {
		path[k] = path1[k];
		seen.insert(path1[k]);
	}
	
	/*
	cerr << "AAA : ";
	for (int k = 0; k < n; k++)
		cerr << path[k] << " ";
	cerr << endl;
	*/
	
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

	/*
	cerr << "BBB " << i << " : ";
	for (int k = 0; k < n; k++)
		cerr << path[k] << " ";
	cerr << endl;
	*/



	for (int k = j+1; k < n; k++) {
		path[k] = not_seen.front();
		not_seen.pop();
	}
	
	/*
	cerr << "CCC " << i << " : ";
	for (int k = 0; k < n; k++)
		cerr << path[k] << " ";
	cerr << endl;
	*/
	
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

void genetic_solver::mutation(Path & path) {
	// 2-OPT mutation
	mt19937 generator(random_device{}());
	int n = path.number_cities();
	int i = uniform_int_distribution<int>(1, n-3)(generator);
	int j = uniform_int_distribution<int>(i+1, n-2)(generator);
	path.reverse(i,j);
}

void genetic_solver::optimize() {
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

Path genetic_solver::get_solution() const {
	return population[0];
}
