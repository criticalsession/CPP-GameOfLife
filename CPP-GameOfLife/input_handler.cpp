#include "input_handler.h"
#include "size_settings.h"
#include <SDL.h>
#include <vector>

void InputHandler::handleInput(SDL_Event& event, std::vector<std::vector<bool>>& grid, bool& running, bool& paused) {
	if (event.type == SDL_QUIT) {
		running = false;
	}

	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_SPACE) {
			paused = !paused;
		}
	}

	if (event.type == SDL_MOUSEBUTTONDOWN && paused) {
		int x, y;
		SDL_GetMouseState(&x, &y);

		int gridX = x / CELL_WIDTH;
		int gridY = y / CELL_HEIGHT;

		flipCell(gridX, gridY, grid);
	}
}

void InputHandler::flipCell(int x, int y, std::vector<std::vector<bool>>& grid) {
	grid[x][y] = !grid[x][y];
}