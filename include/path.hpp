#ifndef PATH_H
#define PATH_H

#include <iostream>
#include <vector>
#include "map.hpp"
#include <json.hpp>

using namespace std;
using json = nlohmann::json;

class Path {
	
public:

	Path(const Map * map, vector<int> path_order);
	
	Path(const Path &path);

	Path & operator=(const Path &path);
	
	static Path random(const Map * map);
	
	int distance() const;
	
	int number_cities() const;
	
	void reverse(int begin, int end);
	
	Path crossing(int begin, int end, const Path & other) const;
	
	static Path read_JSON_file(string json_file_name);
	
	static Path JSON_to_path(json json_path);
	
	void write_JSON_file(string json_file_name) const;
	
	json path_to_JSON() const;
	
	int operator[](int i) const;
	
	int & operator[](int i);
	
	vector<int>::iterator begin();
	
	vector<int>::iterator end();
	
	bool operator==(const Path & path) const;
	
	friend ostream & operator<<(ostream & os, const Path & path);

private :
	
	const Map * map;
	
	vector<int> path_order;

};

#endif
