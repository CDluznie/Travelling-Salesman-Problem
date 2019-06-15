#include "SDL_drawer.hpp"
#include <stdexcept>

SDL_drawer::SDL_drawer(int width, int height) : 
	width(width),
	height(height),
	window(nullptr),
	renderer(nullptr),
	map(nullptr) { 
		
}

SDL_drawer::SDL_drawer(const SDL_drawer &drawer) :  
	width(drawer.width),
	height(drawer.height),
	window(drawer.window),
	renderer(drawer.renderer),
	map(drawer.map) {

}

SDL_drawer & SDL_drawer::operator=(const SDL_drawer &drawer) {
	if (&drawer != this) {
		SDL_drawer tmp(drawer);
		swap(width, tmp.width);
		swap(height, tmp.height);
		swap(window, tmp.window);
		swap(renderer, tmp.renderer);
		swap(map, tmp.map);
	}
	return *this;
}

SDL_drawer::~SDL_drawer() {
	SDL_DestroyRenderer(renderer); 
	SDL_DestroyWindow(window);
};

void SDL_drawer::initialize(const Map * map) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw std::runtime_error("SDL could not be initialized: " + string(SDL_GetError()));
	}
	window = SDL_CreateWindow(
        "travelling salesman problem",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_OPENGL
    );
    if (window == nullptr) {
		throw std::runtime_error("Window could not be created: " + string(SDL_GetError()));
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		throw std::runtime_error("Renderer could not be created: " + string(SDL_GetError()));
	}
	this->map = map;
	clean();
}

void SDL_drawer::draw_line(int x1, int y1, int x2, int y2) const {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
	SDL_RenderPresent(renderer);

}

void SDL_drawer::draw_city(const City & city) const {
	int size = 5;
	draw_line(city.getX() - size, city.getY(), city.getX() + size, city.getY());
	draw_line(city.getX(), city.getY() - size, city.getX(), city.getY() + size);
}

void SDL_drawer::draw_path_city(const City & city1, const City & city2) const {
	draw_line(city1.getX(), city1.getY(), city2.getX(), city2.getY());
}

void SDL_drawer::draw_map() const {
	for (int i = 0; i < map->number_cities(); i++) {
		draw_city((*map)[i]);
	}
}

void SDL_drawer::draw_path(const Path & path) const {
	for (int i = 0; i < path.number_cities()-1; i++) {
		draw_path_city((*map)[path[i]], (*map)[path[i+1]]);
	}
}

void SDL_drawer::wait_key() const {
	bool done = false;
	while (!done) {
		SDL_Event event{};
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				done = true;
			}
			if (event.type == SDL_QUIT) { //TODO
				exit(0);
			}
		}	
	}
}

void SDL_drawer::clean() const {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}
