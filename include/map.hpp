#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include "city.hpp"
#include <json.hpp>

using namespace std;
using json = nlohmann::json;

class Map {
	
public:

	Map(int min_x, int max_x, int min_y, int max_y, vector<City> cities);
	
	Map(const Map &map);
	
	static Map * random(int n, int xmin, int xmax, int ymin, int ymax);
	
	int number_cities() const;
	
	int x_min() const;
	
	int x_max() const;
	
	int y_min() const;
	
	int y_max() const;
	
	City operator[](int i) const;
	
	static Map * read_JSON_file(string json_file_name);
	
	static Map * JSON_to_map(json json_map);
	
	void write_JSON_file(string json_file_name) const;
	
	json map_to_JSON() const;
	
	friend ostream & operator<< (ostream & os, const Map & map);

private :
	
	//TODO reference_wrapper or shared_ptr
	int min_x;
	int max_x;
	int min_y;
	int max_y;
	vector<City> cities;

};

#endif
