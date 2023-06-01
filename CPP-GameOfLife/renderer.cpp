#include "renderer.h"
#include "size_settings.h"
#include <SDL.h>
#include <vector>

void Renderer::renderGrid(SDL_Renderer* renderer, const std::vector<std::vector<bool>>& grid) {
	for (int x = 0; x < GRID_WIDTH; x++) {
		for (int y = 0; y < GRID_HEIGHT; y++) {
			SDL_Rect cell;
			cell.x = x * CELL_WIDTH;
			cell.y = y * CELL_HEIGHT;
			cell.w = CELL_WIDTH;
			cell.h = CELL_HEIGHT;

			if (grid[x][y]) {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // alive
			}
			else {
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // dead
			}

			SDL_RenderFillRect(renderer, &cell);
		}
	}
}