#ifndef SDL_DRAWER_HPP
#define SDL_DRAWER_HPP

#include <SDL.h>
#include "map.hpp"
#include "path.hpp"

using namespace std;

class SDL_drawer {
	
public:
    
    explicit SDL_drawer(int width, int height);
        
	SDL_drawer(const SDL_drawer &drawer);

	SDL_drawer &operator=(const SDL_drawer &drawer);

	// todo keep if interface or delete if factory
	void initialize();

	void draw_map(const Map & map) const; 
	
	void draw_path(const Map & map, const Path & path) const; 
	
	// draw path
	//void dessineLigne(float x1, float y1, float x2, float y2) const override;

	void wait_key() const;

	void clean() const;
        
	~SDL_drawer();

private:
    
	int width;
	int height;
	SDL_Window *window;
	SDL_Renderer *renderer;

	void draw_line(int x1, int y1, int x2, int y2) const;
	
	void draw_city(const City & city) const;
	
	void draw_path_city(const City & city1, const City & city2) const; 

};

#endif
