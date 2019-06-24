#ifndef CITY_H
#define CITY_H

#include <iostream>
#include <string>
#include <json.hpp>

using namespace std;
using json = nlohmann::json;

class City {
	
public:

    City(int x, int y);
    
    int getX() const;
    
    int getY() const;
    
    int distance(const City & city) const;
    
    static City JSON_to_city(json json_city);
    
	json city_to_JSON() const;
    
    friend ostream & operator<< (ostream & os, const City & city);
    
private :

    int x;
	int y;

};

#endif
