#ifndef PATH_H
#define PATH_H

#include <iostream>
#include <vector>
#include "map.hpp"

using namespace std;

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
