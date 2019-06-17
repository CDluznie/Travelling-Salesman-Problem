#ifndef PATH_H
#define PATH_H

#include <iostream>
#include <vector>
#include "map.hpp"

using namespace std;

class Path {
	
public:

	Path(vector<int> path_order); // Todo private ?
	
	Path(const Path &path);

	Path & operator=(const Path &path);
	
	static Path random(const Map & map); // TODO maybe in Map
	
	int distance() const; // TODO maybe in Solver
	
	int number_cities() const;
	
	int operator[](int i) const;
	
	int & operator[](int i);
	
	vector<int>::iterator begin();
	
	vector<int>::iterator end();
	
	friend ostream & operator<< (ostream & os, const Path & path);

private :
	
	vector<int> path_order;

};

#endif
