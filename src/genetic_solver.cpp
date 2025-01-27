#include "genetic_solver.hpp"
#include <algorithm>
#include <random>
#include <set>
#include <queue>

genetic_solver::genetic_solver(vector<Path> population, int number_path_crossover, int number_path_mutation) :
	population(population),
	number_path_crossover(number_path_crossover),
	number_path_mutation(number_path_mutation) {

}

genetic_solver * genetic_solver::create(const Map * map, int population_size, float rate_path_crossover, float rate_path_mutation) {
	vector<Path> population;
	for (int i = 0; i < population_size; i++) {
		population.push_back(Path::random(map));
	}
	sort(population.begin(), population.end(), [](const Path & p1, const Path & p2) {
		return fitness(p1) < fitness(p2);
	});
	return new genetic_solver(population, population_size*rate_path_crossover, population_size*rate_path_mutation);
}

int genetic_solver::fitness(const Path & path) {
	return path.distance();
}

Path genetic_solver::cross_over(const Path & path1, const Path & path2) {
	// OX crossover
	mt19937 generator(random_device{}());
	int n = path1.number_cities();
	int i = uniform_int_distribution<int>(1, n-3)(generator);
	int j = uniform_int_distribution<int>(i+1, n-2)(generator);
	return path1.crossing(i, j, path2);
}

void genetic_solver::mutation(Path & path) {
	// 2-OPT mutation
	mt19937 generator(random_device{}());
	int n = path.number_cities();
	int i = uniform_int_distribution<int>(1, n-3)(generator);
	int j = uniform_int_distribution<int>(i+1, n-2)(generator);
	path.reverse(i,j);
}

vector<Path> genetic_solver::merge(const vector<Path> & population, const vector<Path> & childs_population) {
	vector<Path> next_population;
	int parent_index = 0;
	int child_index = 0;
	for (unsigned int i = 0; i <  population.size(); i++) {
		if (fitness(population[parent_index]) < fitness(childs_population[child_index])) {
			next_population.push_back(population[parent_index++]);
		} else {
			next_population.push_back(childs_population[child_index++]);
		}
	}
	return next_population;
}

void genetic_solver::optimize() {
	vector<Path> childs_population;
	for (unsigned int i = 0; i <  population.size(); i++) {
		childs_population.push_back(cross_over(population[(2*i) % number_path_crossover], population[(2*i + 1) % number_path_crossover]));
	}
	for_each(childs_population.begin(), childs_population.begin()+number_path_mutation, [](Path & p) {
		mutation(p);
	});
	sort(childs_population.begin(), childs_population.end(), [](const Path & p1, const Path & p2) {
		return fitness(p1) < fitness(p2);
	});
	population = merge(population, childs_population);
}

Path genetic_solver::get_solution() const {
	return population[0];
}
