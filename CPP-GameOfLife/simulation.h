#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>

class Simulation {
public:
	void updateGrid(std::vector<std::vector<bool>>& grid);
private:
	int getLiveNeighbours(int x, int y, std::vector<std::vector<bool>>& grid);
};
#endif