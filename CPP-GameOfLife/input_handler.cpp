#include "size_settings.h"
#include "input_handler.h"

#include <SDL.h>
#include <vector>

using std::vector;

void InputHandler::handleInput(SDL_Event& event, vector<vector<bool>>& grid, bool& running, bool& paused, int& fps, int& frameDelay) {
	if (event.type == SDL_QUIT) {
		running = false;
	}

	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_SPACE) {
			paused = !paused;
		}
		else if (event.key.keysym.sym == SDLK_UP) {
			if (fps < 60) frameDelay = 1000 / ++fps;
		}
		else if (event.key.keysym.sym == SDLK_DOWN) {
			if (fps > 1) frameDelay = 1000 / --fps;
		}
	}

	if (event.type == SDL_MOUSEBUTTONDOWN && paused) {
		int x, y;
		SDL_GetMouseState(&x, &y);

		int gridX = x / CELL_WIDTH;
		int gridY = (y - TOP_PADDING) / CELL_HEIGHT;

		flipCell(gridX, gridY, grid);
	}
}

void InputHandler::flipCell(int x, int y, vector<vector<bool>>& grid) {
	grid[x][y] = !grid[x][y];
}