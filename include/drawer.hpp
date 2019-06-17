#ifndef DRAWER_HPP
#define DRAWER_HPP

#include "path.hpp"

using namespace std;

class Drawer {
	
public:
	
	virtual ~Drawer() {};
	
	virtual void initialize(const Map & map, int x_min, int x_max, int y_min, int y_max) = 0;
	
	virtual void draw_map() const = 0;
	
	virtual void draw_path(const Path & path) const = 0; 
	
	virtual void clean() const = 0;

	virtual void update() const = 0;
	
	virtual bool stop() const = 0;

};

#endif