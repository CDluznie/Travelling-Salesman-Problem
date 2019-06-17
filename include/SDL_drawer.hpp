#ifndef SDL_DRAWER_HPP
#define SDL_DRAWER_HPP

#include <SDL2/SDL.h>
#include <vector>
#include "map.hpp"
#include "path.hpp"
#include "drawer.hpp"

using namespace std;

class SDL_drawer : public Drawer {
	
public:

    explicit SDL_drawer(int width, int height);
        
	SDL_drawer(const SDL_drawer &drawer);

	SDL_drawer &operator=(const SDL_drawer &drawer);
	
	~SDL_drawer();

	void initialize(const Map & map, int x_min, int x_max, int y_min, int y_max) override;
	
	void draw_map() const override;
	
	void draw_path(const Path & path) const override; 
	
	void clean() const override;

	void update() const override;
	
	bool stop() const override;

private:

	int width;
	int height;
	SDL_Window * window;
	SDL_Renderer * renderer;
	vector<int> positions_x;
	vector<int> positions_y;

	int linear_scaling(int x, int min_x, int max_x, int min_val, int max_val) const;

	void draw_city(int city_index) const;
	
	void draw_path_city(int city_index1, int city_index2) const; 

};

#endif
