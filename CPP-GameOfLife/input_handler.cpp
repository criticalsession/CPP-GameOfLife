#include "size_settings.h"
#include "input_handler.h"
#include "renderer.h"

#include <SDL.h>

void InputHandler::handleInput(SDL_Event& event, bool(&grid)[GRID_WIDTH][GRID_HEIGHT], bool& running, bool& paused, int& fps, int& frameDelay, Renderer& renderer) {
	if (event.type == SDL_QUIT) {
		running = false;
	}

	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_SPACE) {
			paused = !paused;
			renderer.changeCursor(paused);
		}
		else if (event.key.keysym.sym == SDLK_c && paused) {
			for (int x = 0; x < GRID_WIDTH; x++) {
				for (int y = 0; y < GRID_HEIGHT; y++) {
					grid[x][y] = false;
				}
			}
		}
		else if (event.key.keysym.sym == SDLK_END && paused) {
			fps = -1;
		}
		else if (event.key.keysym.sym == SDLK_UP && paused) {
			if (fps == -1) {
				fps = 16;
				frameDelay = 1000 / 16;
			}
			else if (fps < 60) frameDelay = 1000 / ++fps;
		}
		else if (event.key.keysym.sym == SDLK_DOWN && paused) {
			if (fps == -1) {
				fps = 16;
				frameDelay = 1000 / 16;
			}
			else if (fps > 1) frameDelay = 1000 / --fps;
		}
	}

	// flip cell with mouse
	static bool mouseHeldDown = false;
	static int lastGridX = -1, lastGridY = -1;

	if (event.type == SDL_MOUSEBUTTONDOWN && paused) {
		findAndFlipCell(lastGridX, lastGridY, grid);
		mouseHeldDown = true;
	}
	else if (event.type == SDL_MOUSEBUTTONUP) {
		mouseHeldDown = false;
		lastGridX = -1;
		lastGridY = -1;
	}
	else if (event.type == SDL_MOUSEMOTION && mouseHeldDown && paused) {
		findAndFlipCell(lastGridX, lastGridY, grid);
	}
}

void InputHandler::findAndFlipCell(int &lastGridX, int &lastGridY, bool(&grid)[GRID_WIDTH][GRID_HEIGHT]) {
	int x, y;
	SDL_GetMouseState(&x, &y);

	if (x > 0 && y > TOP_PADDING && y < WINDOW_HEIGHT - BOTTOM_PADDING) {
		int gridX = x / CELL_WIDTH;
		int gridY = (y - TOP_PADDING) / CELL_HEIGHT;

		if (gridX != lastGridX || gridY != lastGridY) {
			flipCell(gridX, gridY, grid);
			lastGridX = gridX;
			lastGridY = gridY;
		}
	}
}

void InputHandler::flipCell(int x, int y, bool(&grid)[GRID_WIDTH][GRID_HEIGHT]) {
	grid[x][y] = !grid[x][y];
}