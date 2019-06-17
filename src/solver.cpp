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
	int population_size = 128;
	for (int i = 0; i < population_size; i++) {
		population.push_back(Path::random(map));
	}
	
	
	sort(population.begin(), population.end(), [this](const Path & p1, const Path & p2) {
		return fitness(p1) < fitness(p2);
	});

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
	vector<int> tmp(n);
	
	int i = 1;
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
		/*
		else
			(*fils)->ordre_parcours[i] = tmp[i];
		*/
    }
	
	
	return Path(tmp);
}

void Solver::mutation(Path & path) const {
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
	int pop = population.size();

	
	
	vector<Path> childs_population;
	
	/*
	for (int i = 0; i < pop; i++) {
		for (int j = 0; j < i; j++) {
			childs_population.push_back(cross_over(population[i], population[j]));
		}
		for (int j = i+1; j < pop; j++) {
			childs_population.push_back(cross_over(population[i], population[j]));
		}
	}
	*/
	/*
	for (int i = 0; i < pop; i++) {
		for (int j = i+1; j < pop; j++) {
			childs_population.push_back(cross_over(population[i], population[j]));
		}
	}
	*/
	
	/*
	mt19937 generator(random_device{}());
	for (int i = 0; i < pop; i++) {
		int a = uniform_int_distribution<int>(0, pop-1)(generator);
		int b = uniform_int_distribution<int>(0, pop-1)(generator);
		childs_population.push_back(cross_over(population[a], population[b]));
	}
	*/
	
	
	int nn = 80;
	for (int i = 0; i < pop; i++) {
		childs_population.push_back(cross_over(population[(2*i) % nn], population[(2*i + 1) % nn]));
	}
	
	
  
	int pppp = 115;
	for_each(childs_population.begin(), childs_population.begin()+pppp, [this](Path & p) {
		mutation(p);
	});
	sort(childs_population.begin(), childs_population.end(), [this](const Path & p1, const Path & p2) {
		return fitness(p1) < fitness(p2);
	});
	
	
	vector<Path> new_population;
	int parent_index = 0;
	int child_index = 0;
	for (int i = 0; i < pop; i++) {
		if (fitness(population[parent_index]) < fitness(childs_population[child_index])) {
			new_population.push_back(population[parent_index++]);
		} else {
			new_population.push_back(childs_population[child_index++]);
		}
	}
	
	
	
	/*
	population.insert(population.end(), childs_population.begin(), childs_population.end());
	sort(population.begin(), population.end(), [this](const Path & p1, const Path & p2) {
		return fitness(p1) < fitness(p2);
	});
	*/
	population = vector<Path>(new_population); // TODO avoid copy
}

Path Solver::get_solution() const {
	return population[0];
}
