#include "solver.hpp"
#include <algorithm>
#include <random>

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
	int n = path1.number_cities();
	vector<int> tmp(n);
	
	mt19937 generator(random_device{}());
	int i = uniform_int_distribution<int>(1, n-2)(generator);
	
	//i = 1;
	int premier = tmp[i] = path1[i];
	int prec = path2[i];
	while (prec != premier) {
		if (path1[i] == prec) {
			tmp[i] = path1[i];
			prec = path2[i];
		}
		i = (i+1)%n;
	}
	for (i = 0 ; i < n ; i++) {
		if (0 == tmp[i])
			tmp[i] = path2[i];

    }
	
	
	return Path(tmp);
}

void Solver::mutation(Path & path) {
	mt19937 generator(random_device{}());
	
	int n = path.number_cities();
	
	int i = uniform_int_distribution<int>(1, n-3)(generator); //TODO extremities
	int j = uniform_int_distribution<int>(i+1, n-2)(generator); //TODO extremities

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
