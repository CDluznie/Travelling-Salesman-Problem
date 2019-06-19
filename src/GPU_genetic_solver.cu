#include "GPU_genetic_solver.hpp"


#include <curand.h>
#include <curand_kernel.h>


#include <algorithm>
#include <random>
#include <set>
#include <queue>

#define HANDLE_ERROR(err) (HandleError(err, __FILE__, __LINE__))

static void HandleError(cudaError_t err, const char *file, const int line) {
	if (err != cudaSuccess) {
        std::string errMsg = 
			string(cudaGetErrorString(err)) +
			" (file:" + string(file) +
			" at line:" + to_string(line) + ")";
        throw std::runtime_error(errMsg);
    }
}

GPU_genetic_solver::GPU_genetic_solver(int2 *dev_map, int map_size, int *dev_population, int *dev_childs_population, int population_size, int number_path_crossover, int number_path_mutation) :
	dev_map(dev_map),
	map_size(map_size),
	dev_population(dev_population),
	dev_childs_population(dev_childs_population),
	population_size(population_size),
	number_path_crossover(number_path_crossover),
	number_path_mutation(number_path_mutation) {

}

GPU_genetic_solver * GPU_genetic_solver::create(const Map & map, int population_size, float rate_path_crossover, float rate_path_mutation) {

	
	/* TODO on GPU */
	vector<Path> population;
	for (int i = 0; i < population_size; i++) {
		population.push_back(Path::random(map));
	}
	sort(population.begin(), population.end(), [&map](const Path & p1, const Path & p2) {
		return fitness(map, p1) < fitness(map, p2);
	});
	/*          */
	

	int map_size = map.number_cities();
	int path_length = map_size + 1;
	
	// Create map on GPU
	vector<int2> host_map;
	for (int i = 0; i < map.number_cities(); i++) {
		City city = map[i];
		host_map.push_back(int2 {city.getX(), city.getY()});
	}
	int2 *dev_map = nullptr;
	HANDLE_ERROR(cudaMalloc(&dev_map, host_map.size()*sizeof(int2)));
	HANDLE_ERROR(cudaMemcpy(dev_map, host_map.data(), host_map.size()*sizeof(int2), cudaMemcpyHostToDevice));
	

	
	// Create paths on GPU
	vector<int> host_population;
	for (int i = 0; i < population_size; i++) {
		host_population.insert(host_population.end(), population[i].begin(), population[i].end());
	}
	int *dev_population = nullptr; 
	HANDLE_ERROR(cudaMalloc(&dev_population, population_size*path_length*sizeof(int)));
	HANDLE_ERROR(cudaMemcpy(dev_population, host_population.data(), host_population.size()*sizeof(int), cudaMemcpyHostToDevice));
	int *dev_childs_population = nullptr; 
	HANDLE_ERROR(cudaMalloc(&dev_childs_population, population_size*path_length*sizeof(int)));



	return new GPU_genetic_solver(dev_map, map_size, dev_population, dev_childs_population, population_size, population_size*rate_path_crossover, population_size*rate_path_mutation);
}

GPU_genetic_solver::~GPU_genetic_solver() {
	HANDLE_ERROR(cudaFree(nullptr));
	HANDLE_ERROR(cudaFree(dev_population));
}

int GPU_genetic_solver::fitness(const Map & map, const Path & path) {
	int d = 0;
	for (int i = 0; i < path.number_cities()-1; i++) {
		d += map[path[i]].distance(map[path[i+1]]);
	}
	return d;
}

__global__
void cross_over(int *dev_population, int *dev_childs_population, int population_size, int path_length) {

	//TODO
	
	for (int i = 0; i < population_size*path_length; i++) {
		dev_childs_population[i] = dev_population[i];
	}
	
}	

Path GPU_genetic_solver::cross_over_tmp(const Path & path1, const Path & path2) {
	mt19937 generator(random_device{}());
	int n = path1.number_cities();
	
	
	/* */
	// OX crossover
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

__global__
void mutation(int *dev_population, int population_size, int path_length) {
	
	
	for (int path = 0; path < population_size; path++) {
		
		
		int begin_index = (((dev_population[path]*path) << 2) | 784) % (path_length-3) + 1; // TODO random
		int end_index = (((dev_population[path]*path) << 3) | 993) % (path_length-begin_index-1) + begin_index; // TODO random
		
		int i = path*path_length + begin_index;
		int j = path*path_length + end_index;
		while (i < j) {
			//
			int tmp = dev_population[i];
			dev_population[i] = dev_population[j];
			dev_population[j] = tmp;
			//
			i++;
			j--;
		}
	}
	
}	

void GPU_genetic_solver::mutation_tmp(Path & path) {
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

void GPU_genetic_solver::optimize() {
	/* TODO RM */
	/* GPU to HOST */
	int path_length = map_size+1;
	
	
	vector<int> host_path_1(population_size*path_length);
	HANDLE_ERROR(cudaMemcpy(host_path_1.data(), dev_population, host_path_1.size()*sizeof(int), cudaMemcpyDeviceToHost));
	vector<Path> population;
	for (int i = 0; i < population_size; i++){
		auto begin_iter = host_path_1.begin() + i*path_length;
		Path path(vector<int>(begin_iter, begin_iter + path_length));
		population.push_back(path);
	}
	
	/* TODO RM */
	/* GPU to HOST */
	vector<int2> host_map(map_size);
	HANDLE_ERROR(cudaMemcpy(host_map.data(), dev_map, map_size*sizeof(int2), cudaMemcpyDeviceToHost));
	vector<City> cities;
	for (int2 point : host_map) {
		cities.push_back(City(point.x, point.y));
	}
	Map map(cities);
	
	
	
	
	cross_over<<<1,1>>>(dev_population, dev_childs_population, population_size, path_length);
	mutation<<<1,1>>>(dev_childs_population, number_path_mutation, path_length);
	
	
	vector<Path> childs_population;
	
	
	// CPU child
	/*
	for (unsigned int i = 0; i <  population.size(); i++) {
		childs_population.push_back(cross_over_tmp(population[(2*i) % number_path_crossover], population[(2*i + 1) % number_path_crossover]));
	}
	for_each(childs_population.begin(), childs_population.begin()+number_path_mutation, [](Path & p) {
		mutation_tmp(p);
	});
	 */

	//GPU child
	/* */
	vector<int> childs_population_host(population_size*path_length);
	HANDLE_ERROR(cudaMemcpy(childs_population_host.data(), dev_childs_population, population_size*path_length*sizeof(int), cudaMemcpyDeviceToHost));
	for (int i = 0; i < population_size; i++){
		auto begin_iter = childs_population_host.begin() + i*path_length;
		Path path(vector<int>(begin_iter, begin_iter + path_length));
		childs_population.push_back(path);
	}
	/* */
	
	
	sort(childs_population.begin(), childs_population.end(), [&map](const Path & p1, const Path & p2) {
		return fitness(map, p1) < fitness(map, p2);
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


	/* TODO RM */
	/* HOST to GPU */
	vector<int> host_population_2;
	for (int i = 0; i < population.size(); i++) {
		host_population_2.insert(host_population_2.end(), population[i].begin(), population[i].end());
	}
	HANDLE_ERROR(cudaMemcpy(dev_population, host_population_2.data(), host_population_2.size()*sizeof(int), cudaMemcpyHostToDevice));
}

Path GPU_genetic_solver::get_solution() const {
	int path_length = map_size+1;
	
	
	vector<int> host_path(path_length);
	HANDLE_ERROR(cudaMemcpy(host_path.data(), dev_population, path_length*sizeof(int), cudaMemcpyDeviceToHost));
	return Path(host_path);
}
