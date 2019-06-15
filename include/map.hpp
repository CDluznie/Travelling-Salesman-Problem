#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include "city.hpp"

using namespace std;

class Map {
	
public:

	Map(vector<City> cities);
	
	Map(const Map &map);
	
	static Map random(int n, int xmin, int xmax, int ymin, int ymax);
	
	int number_cities() const;
	
	City operator[](int i) const;
	
	friend ostream & operator<< (ostream & os, const Map & map);

private :
	
	//TODO reference_wrapper or shared_ptr
	vector<City> cities;

};

#endif
