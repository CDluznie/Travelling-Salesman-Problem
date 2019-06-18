BIN=tsp

SRC=src
HEADER=include
OBJDIR=obj

CC=g++
FLAGS=-std=c++14 -Wall -Wfatal-errors -Weffc++

NVCC=nvcc
FLAGS_NVCC=-std=c++14 -gencode=arch=compute_60,code=sm_60 

INC=-I./$(HEADER) -I/usr/include/SDL2 -I/usr/local/cuda/include
LIBDIR=
LIBS=-lcuda -lcudart -lSDL2

OBJECTS=$(OBJDIR)/city.o $(OBJDIR)/map.o $(OBJDIR)/path.o $(OBJDIR)/solver.o $(OBJDIR)/drawer.o $(OBJDIR)/SDL_drawer.o
OBJECTS_CUDA=$(OBJDIR)/main.cu.o $(OBJDIR)/GPU_genetic_solver.cu.o

all: init $(OBJECTS) $(OBJECTS_CUDA)
	$(NVCC) $(LIBDIR) $(LIBS) $(FLAGS_NVCC) $(OBJECTS) $(OBJECTS_CUDA) -o $(BIN)

init:
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRC)/%.cpp
	$(CC) $(INC) $(FLAGS) -c $< -o $@

$(OBJDIR)/%.cu.o: $(SRC)/%.cu
	$(NVCC) $(FLAGS_NVCC) $(INC) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	rm -f $(BIN)


