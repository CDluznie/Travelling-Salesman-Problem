#include "path.hpp"
#include <numeric>
#include <random>
#include <algorithm>
#include <set>
#include <queue>

Path::Path(const Map * map, vector<int> path_order) : map(map), path_order(path_order) {
		
}

Path::Path(const Path &path) : map(path.map), path_order(path.path_order) {
	
}

Path & Path::operator=(const Path &path) {
	if (&path != this) {
		Path tmp(path);
		swap(path_order, tmp.path_order);
	}
	return *this;
	
}

Path Path::random(const Map * map) {
	vector<int> path_order(map->number_cities());
	iota(path_order.begin(), path_order.end(), 0);
	path_order.push_back(0);
	shuffle(path_order.begin()+1, path_order.end()-1, mt19937{random_device{}()});
	return Path(map, path_order);
}

int Path::distance() const {
	int d = 0;
	for (unsigned int i = 0; i < path_order.size()-1; i++) {
		d += (*map)[path_order[i]].distance((*map)[path_order[i+1]]);
	}
	return d;
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

Path Path::crossing(int begin, int end, const Path & other) const {
	int n = path_order.size();
	vector<int> new_path = vector<int>(n);
	set<int> seen;
	for (int i = begin; i <= end; i++) {
		new_path[i] = path_order[i];
		seen.insert(path_order[i]);
	}
	queue<int> not_seen;
	for (int i = 0; i < n; i++) {
		if (seen.find(other.path_order[i]) == seen.end()) {
			not_seen.push(other.path_order[i]);
		}
	}
	for (int i = 0; i < begin; i++) {
		new_path[i] = not_seen.front();
		not_seen.pop();
	}
	for (int i = end+1; i < n; i++) {
		new_path[i] = not_seen.front();
		not_seen.pop();
	}
	return Path(other.map, new_path);
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
