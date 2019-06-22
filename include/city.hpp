#ifndef CITY_H
#define CITY_H

#include <iostream>
#include <string>

using namespace std;

class City {
	
public:

    City(int x, int y);
    
    int getX() const;
    
    int getY() const;
    
    int distance(const City & city) const;
    
    friend ostream & operator<< (ostream & os, const City & city);
    
private :

    int x;
	int y;

};

#endif
