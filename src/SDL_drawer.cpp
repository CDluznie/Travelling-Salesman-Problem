#include "SDL_drawer.hpp"
#include <stdexcept>

SDL_drawer::SDL_drawer(int width, int height, SDL_Window * window, SDL_Renderer * renderer, vector<int> positions_x, vector<int> positions_y) : 
	width(width),
	height(height),
	window(window),
	renderer(renderer),
	positions_x(positions_x),
	positions_y(positions_y) { 
		
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

SDL_drawer * SDL_drawer::create(int width, int height, const Map & map) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw std::runtime_error("SDL could not be initialized: " + string(SDL_GetError()));
	}
	SDL_Window * window = SDL_CreateWindow(
        "Travelling Salesman Problem",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_OPENGL
    );
    if (window == nullptr) {
		throw std::runtime_error("Window could not be created: " + string(SDL_GetError()));
	}
	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		throw std::runtime_error("Renderer could not be created: " + string(SDL_GetError()));
	}
	int border = 10;
	int x_min = map.x_min(), x_max = map.x_max();
	int y_min = map.y_min(), y_max = map.y_max();
	vector<int> positions_x;
	vector<int> positions_y;
	for (int i = 0; i < map.number_cities(); i++) {
		positions_x.push_back(linear_scaling(map[i].getX(), x_min, x_max, border, width-border-1));
		positions_y.push_back(linear_scaling(map[i].getY(), y_min, y_max, border, height-border-1));
	}
	SDL_drawer * drawer = new SDL_drawer(width, height, window, renderer, positions_x, positions_y);
	drawer->clean();
	return drawer;
}

SDL_drawer::~SDL_drawer() {
	SDL_DestroyRenderer(renderer); 
	SDL_DestroyWindow(window);
	SDL_Quit();
};

int SDL_drawer::linear_scaling(int x, int min_x, int max_x, int min_val, int max_val) {
	return min_val + static_cast<int>((max_val - min_val)*(static_cast<float>(x - min_x)/(max_x - min_x)));
}

void SDL_drawer::draw_city(int city_index) const {
	int size = 5;
	int x = positions_x[city_index];
	int y = positions_y[city_index];
	SDL_RenderDrawLine(renderer, x-size, y, x+size, y);
	SDL_RenderDrawLine(renderer, x, y-size, x, y+size);
}

void SDL_drawer::draw_path_city(int city_index1, int city_index2) const {
	int x1 = positions_x[city_index1];
	int y1 = positions_y[city_index1];
	int x2 = positions_x[city_index2];
	int y2 = positions_y[city_index2];
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void SDL_drawer::draw_map() const {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	for (unsigned int i = 0; i < positions_x.size(); i++) {
		draw_city(i);
	}
}

void SDL_drawer::draw_path(const Path & path) const {
	SDL_SetRenderDrawColor(renderer, 50, 50, 255, 255);
	for (int i = 0; i < path.number_cities()-1; i++) {
		draw_path_city(path[i], path[i+1]);
	}
	draw_map();
}

void SDL_drawer::draw_stats(const Path & path) const {
	static int n = 0;
	if (n == 0) {
		cout << path.distance() << endl;
	}
	n = (n+1)%50;
}

bool SDL_drawer::stop() const {
	SDL_Event event{};
	bool stop = false;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
			stop = true;
		} else if (event.type == SDL_QUIT) {
			stop = true;
		}
	}
	return stop;
}

void SDL_drawer::clean() const {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void SDL_drawer::update() const {
	SDL_RenderPresent(renderer);
}
