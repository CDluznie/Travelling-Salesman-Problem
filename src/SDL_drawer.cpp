#include "SDL_drawer.hpp"
#include <stdexcept>

SDL_drawer::SDL_drawer(int width, int height) : 
	width(width),
	height(height),
	window(nullptr),
	renderer(nullptr),
	positions_x(),
	positions_y() { 
		
}

SDL_drawer::SDL_drawer(const SDL_drawer &drawer) :  
	width(drawer.width),
	height(drawer.height),
	window(drawer.window),
	renderer(drawer.renderer),
	positions_x(drawer.positions_x),
	positions_y(drawer.positions_y) {

}

SDL_drawer & SDL_drawer::operator=(const SDL_drawer &drawer) {
	if (&drawer != this) {
		SDL_drawer tmp(drawer);
		swap(width, tmp.width);
		swap(height, tmp.height);
		swap(window, tmp.window);
		swap(renderer, tmp.renderer);
		swap(positions_x, tmp.positions_x);
		swap(positions_y, tmp.positions_y);
	}
	return *this;
}

SDL_drawer::~SDL_drawer() {
	SDL_DestroyRenderer(renderer); 
	SDL_DestroyWindow(window);
};

void SDL_drawer::initialize(const Map & map, int x_min, int x_max, int y_min, int y_max) {
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
	for (int i = 0; i < map.number_cities(); i++) {
		positions_x.push_back(linear_scaling(map[i].getX(), x_min, x_max, 0, width-1));
		positions_y.push_back(linear_scaling(map[i].getY(), y_min, y_max, 0, height-1));
	}
	clean();
}

int SDL_drawer::linear_scaling(int x, int min_x, int max_x, int min_val, int max_val) const {
	return min_val + static_cast<int>((max_val - min_val)*(static_cast<float>(x - min_x)/(max_x - min_x)));
}

void SDL_drawer::draw_line(int x1, int y1, int x2, int y2, int r, int g, int b) const {
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
	SDL_RenderPresent(renderer);
}

void SDL_drawer::draw_city(int city_index) const {
	int size = 5;
	int r = 255, g = 0, b = 0;
	draw_line(positions_x[city_index] - size, positions_y[city_index], positions_x[city_index] + size, positions_y[city_index], r, g, b);
	draw_line(positions_x[city_index], positions_y[city_index] - size, positions_x[city_index], positions_y[city_index] + size, r, g, b);
}

void SDL_drawer::draw_path_city(int city_index1, int city_index2) const {
	int r = 50, g = 50, b = 255;
	draw_line(positions_x[city_index1], positions_y[city_index1], positions_x[city_index2], positions_y[city_index2], r, g, b);
}

void SDL_drawer::draw_map() const {
	for (unsigned int i = 0; i < positions_x.size(); i++) {
		draw_city(i);
	}
}

void SDL_drawer::draw_path(const Path & path) const {
	for (int i = 0; i < path.number_cities()-1; i++) {
		draw_path_city(path[i], path[i+1]);
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
