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
    
    int distance(const City & city) const; // TODO maybe squared distance
    
    //Status_Return_Ville ville_distance (const Ville *v, const Ville *w, int *resultat);
	
	// operator== int ville_sont_egale (const Ville *v, const Ville *w);
	// operator!= int ville_sont_egale (const Ville *v, const Ville *w);
    
    friend ostream & operator<< (ostream & os, const City & city);
    
    // operator>>

private :

    int x;
	int y;

};

#endif
