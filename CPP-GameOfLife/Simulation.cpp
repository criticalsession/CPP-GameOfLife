#include "simulation.h"
#include "size_settings.h"

int Simulation::getLiveNeighbours(int x, int y, bool(&grid)[GRID_WIDTH][GRID_HEIGHT]) {
	int liveNeighbours = 0;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0) continue;

			int nx = x + i;
			int ny = y + j;

			if (nx < 0) nx = GRID_WIDTH - 1;
			if (ny < 0) ny = GRID_HEIGHT - 1;
			if (nx > GRID_WIDTH - 1) nx = 0;
			if (ny > GRID_HEIGHT - 1) ny = 0;

			if (nx >= 0 && ny >= 0 && nx < GRID_WIDTH && ny < GRID_HEIGHT && grid[nx][ny]) {
				liveNeighbours++;
			}
		}
	}

	return liveNeighbours;
}

void Simulation::updateGrid(bool(&grid)[GRID_WIDTH][GRID_HEIGHT]) {
	bool newGrid[GRID_WIDTH][GRID_HEIGHT];

	for (int x = 0; x < GRID_WIDTH; x++) {
		for (int y = 0; y < GRID_HEIGHT; y++) {
			int liveNeighbours = getLiveNeighbours(x, y, grid);
			if (grid[x][y]) { // already alive
				if (liveNeighbours < 2 || liveNeighbours > 3) {
					newGrid[x][y] = false; // cell died
				}
				else newGrid[x][y] = grid[x][y];
			}
			else {
				if (liveNeighbours == 3) {
					newGrid[x][y] = true; // cell becomes alive
				}
				else newGrid[x][y] = grid[x][y];
			}
		}
	}

	// Copy newGrid back to grid
	for (int i = 0; i < GRID_WIDTH; ++i) {
		for (int j = 0; j < GRID_HEIGHT; ++j) {
			grid[i][j] = newGrid[i][j];
		}
	}
}

void Simulation::initGrid(bool(&grid)[GRID_WIDTH][GRID_HEIGHT]) {
	for (int x = 0; x < GRID_WIDTH; x++) {
		for (int y = 0; y < GRID_HEIGHT; y++) {
			grid[x][y] = false;
		}
	}
}