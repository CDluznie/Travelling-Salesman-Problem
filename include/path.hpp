#ifndef PATH_H
#define PATH_H

#include <iostream>
#include <vector>
#include "map.hpp"

using namespace std;

class Path {
	
public:

	Path(vector<int> path_order); // Todo private ?
	
	static Path random(const Map & map);
	
	// length
	
	int number_cities() const;
	
	int operator[](int i) const;
	
	friend ostream & operator<< (ostream & os, const Path & path);

private :
	
	vector<int> path_order;

};

#endif
