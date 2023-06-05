#ifndef SIMULATION_H
#define SIMULATION_H

#include "size_settings.h"

class Simulation {
public:
	void updateGrid(bool(&grid)[GRID_WIDTH][GRID_HEIGHT]);
	void initGrid(bool(&grid)[GRID_WIDTH][GRID_HEIGHT]);
private:
	int getLiveNeighbours(int x, int y, bool(&grid)[GRID_WIDTH][GRID_HEIGHT]);
};
#endif