#include "city.hpp"

City::City(int x, int y) : x(x), y(y) {

};

int City::getX() const {
	return x;
}
    
int City::getY() const {
	return y;
}

int City::distance(const City & city) const {
	int dx = x - city.x;
	int dy = y - city.y;
	return dx*dx + dy*dy;
}

ostream & operator<< (ostream & os, const City & city) {
	os << "City(" << city.x << ", " << city.y << ")";
    return os;
}
