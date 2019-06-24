#include "map.hpp"
#include <random>
#include <fstream>

Map::Map(int min_x, int max_x, int min_y, int max_y, vector<City> cities) : 
	min_x(min_x),
	max_x(max_x),
	min_y(min_y),
	max_y(max_y),
	cities(cities) {
		
}

Map::Map(const Map &map) : 
	min_x(map.min_x),
	max_x(map.max_x),
	min_y(map.min_y),
	max_y(map.max_y),
	cities(map.cities) {
	
}

Map Map::random(int n, int xmin, int xmax, int ymin, int ymax) {
	vector<City> cities;
	mt19937 generator(random_device{}());
	uniform_int_distribution<int> distribution_x(xmin,xmax);
	uniform_int_distribution<int> distribution_y(ymin,ymax);
	for (int i = 0; i < n; i++) {
		cities.push_back(City(distribution_x(generator), distribution_y(generator)));
	}	
	return Map(xmin, xmax, ymin, ymax, cities);
}

int Map::number_cities() const {
	return cities.size();
}

int Map::x_min() const {
	return min_x;
}
	
int Map::x_max() const {
	return max_x;
}
	
int Map::y_min() const {
	return min_y;
}
	
int Map::y_max() const {
	return max_y;
}

City Map::operator[](int i) const {
	return cities[i];
}

Map Map::read_JSON_file(string json_file_name) {
	json json_map;
	ifstream json_file(json_file_name);
	json_file >> json_map;
	json_file.close();
	return JSON_to_map(json_map);
}

Map Map::JSON_to_map(json json_map) {
	//TODO
	
	int number_cities = 150;
	int x_min = 100, x_max = 999;
	int y_min = 100, y_max = 999;
	
	return Map::random(number_cities, x_min, x_max, y_min, y_max);
}

void Map::write_JSON_file(string json_file_name) const {
	//TODO
}

ostream & operator<< (ostream & os, const Map & map) {
	for (City city : map.cities) {
		os << city << endl;
	}
    return os;
}
