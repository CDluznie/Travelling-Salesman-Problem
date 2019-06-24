BIN=tsp

SRC=src
HEADER=include
OBJDIR=obj

CC=g++
FLAGS=-std=c++14 -Wall -Wfatal-errors -Weffc++
INC=-I./$(HEADER) -I/usr/include/SDL2 -I./third-party/json3.0/include
LIBDIR=
LIBS=-lSDL2

OBJECTS=$(OBJDIR)/city.o $(OBJDIR)/map.o $(OBJDIR)/path.o $(OBJDIR)/solver.o $(OBJDIR)/genetic_solver.o $(OBJDIR)/drawer.o $(OBJDIR)/SDL_drawer.o $(OBJDIR)/main.o

all: init $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BIN) $(LIBDIR) $(LIBS)

init:
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRC)/%.cpp
	$(CC) $(INC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	rm -f $(BIN)


