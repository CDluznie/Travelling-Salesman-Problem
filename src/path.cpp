#include "path.hpp"
#include <numeric>
#include <random>
#include <algorithm>
#include <set>
#include <queue>

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
	path_order.push_back(0);
	shuffle(path_order.begin()+1, path_order.end()-1, mt19937{random_device{}()});
	return Path(path_order);
}

int Path::distance() const {
	return 100; //TODO
}

int Path::number_cities() const {
	return path_order.size();
}

void Path::reverse(int begin, int end) {
	int i = begin;
	int j = end;
	while (i < j) {
		swap(path_order[i], path_order[j]);
		i++;
		j--;
	}
}

Path Path::crossing(int begin, int end, const Path & other) {
	/*
	Path path = Path(vector<int>(path_order.size()));
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
	*/
	return *this;
}

int Path::operator[](int i) const {
	return path_order[i];
}

int & Path::operator[](int i) {
	return path_order[i];
}

vector<int>::iterator Path::begin() {
	return path_order.begin();
}

vector<int>::iterator Path::end() {
	return path_order.end();
}

bool Path::operator==(const Path & path) const {
	if (path_order.size() != path.path_order.size()) {
		return false;
	}
	for (unsigned int i = 0; i < path_order.size(); i++) {
		if (path_order[i] != path.path_order[i]) {
			return false;
		}
	}
	return true;
}

ostream & operator<< (ostream & os, const Path & path) {
	for (int index : path.path_order) {
		os << index << " ";
	}
    return os;
}
