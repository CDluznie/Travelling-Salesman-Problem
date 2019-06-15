#include "map.hpp"
#include <random>

Map::Map(vector<City> cities) : cities(cities) {
		
}

Map::Map(const Map &map) : cities(map.cities) {
	
}

Map Map::random(int n, int xmin, int xmax, int ymin, int ymax) {
	vector<City> cities;
	mt19937 generator(random_device{}());
	uniform_int_distribution<int> distribution_x(xmin,xmax);
	uniform_int_distribution<int> distribution_y(ymin,ymax);
	for (int i = 0; i < n; i++) {
		cities.push_back(City(distribution_x(generator), distribution_y(generator)));
	}	
	return Map(cities);
}

int Map::number_cities() const {
	return cities.size();
}

City Map::operator[](int i) const {
	return cities[i];
}

ostream & operator<< (ostream & os, const Map & map) {
	for (City city : map.cities) {
		os << city << endl;
	}
    return os;
}
