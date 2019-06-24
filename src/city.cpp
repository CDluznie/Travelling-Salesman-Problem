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

City City::JSON_to_city(json json_city) {
	return City(0,0); //TODO
}

json City::city_to_JSON() const {
	json json_city;
	//TODO
	return json_city;
}

ostream & operator<< (ostream & os, const City & city) {
	os << "City(" << city.x << ", " << city.y << ")";
    return os;
}
