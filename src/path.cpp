#include "path.hpp"
#include <numeric>
#include <random>
#include <algorithm>

Path::Path(vector<int> path_order) : path_order(path_order) {
		
}

Path::Path(const Path &path) : path_order(path.path_order) {
	
}

Path & Path::operator=(const Path &path) {
	if (&path != this) {
		Path tmp(path);
		swap(path_order, tmp.path_order);
	}
	return *this;
	
}

Path Path::random(const Map & map) {
	vector<int> path_order(map.number_cities());
	iota(path_order.begin(), path_order.end(), 0);
	shuffle(path_order.begin()+1, path_order.end()-1, mt19937{random_device{}()});
	return Path(path_order);
}

int Path::distance() const {
	return 100;
}

int Path::number_cities() const {
	return path_order.size(); //TODO
}

int Path::operator[](int i) const {
	return path_order[i];
}

int & Path::operator[](int i) {
	return path_order[i];
}


ostream & operator<< (ostream & os, const Path & path) {
	for (int index : path.path_order) {
		os << index << " ";
	}
    return os;
}
