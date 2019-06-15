SRC=src
HEADER=include

CC=g++
CFLAGS=-std=c++14 -Wall -Wfatal-errors -Weffc++ -I./$(HEADER) -I/usr/include/SDL2
LDFLAGS=-lSDL2

all: main

city.o: $(SRC)/city.cpp $(HEADER)/city.hpp
map.o: $(SRC)/map.cpp $(HEADER)/map.hpp $(HEADER)/city.hpp
path.o: $(SRC)/path.cpp $(HEADER)/path.hpp $(HEADER)/map.hpp
SDL_drawer.o: $(SRC)/SDL_drawer.cpp $(HEADER)/SDL_drawer.hpp
main.o: $(SRC)/main.cpp $(HEADER)/city.hpp $(HEADER)/map.hpp $(HEADER)/path.hpp $(HEADER)/SDL_drawer.hpp

main: city.o map.o path.o SDL_drawer.o main.o

%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) -c $<

%: %.o
	$(CC) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf *.o
	
mrproper: clean
	rm -rf main
