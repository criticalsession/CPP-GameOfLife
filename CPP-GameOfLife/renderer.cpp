#include "renderer.h"
#include "size_settings.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <string>
#include <iostream>

void Renderer::drawText(SDL_Renderer* renderer, const std::string& text, int x, int y, int fontSize) {
	TTF_Font* font = TTF_OpenFont("ARIAL.TTF", fontSize);
	SDL_Color color = { 255, 255, 255, 255 };  // White text

	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect dstRect = { x, y, surface->w, surface->h };
	SDL_RenderCopy(renderer, texture, NULL, &dstRect);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
}

void Renderer::drawTitleAndInstructions(SDL_Renderer* renderer, bool paused) {
	if (paused) {
		drawText(renderer, "Conway's Game of Life (PAUSED)", 20, 20, 24);

		drawText(renderer, "Click to flip cells. Press SPACE to unpause.", 20, 50, 16);
		drawText(renderer, "+/- to adjust FPS. Current: 24", 20, 70, 16);
	}
	else {
		drawText(renderer, "Conway's Game of Life", 20, 20, 24);

		drawText(renderer, "Press SPACE to pause and draw cells.", 20, 50, 16);
	}
}
void Renderer::renderGrid(SDL_Renderer* renderer, const std::vector<std::vector<bool>>& grid, bool paused) {
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
				if (!paused) SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // dead
				else {
					if ((x + y) % 2 == 0) {
						SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
					}
					else {
						SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
					}
				}
			}

			SDL_RenderFillRect(renderer, &cell);
		}
	}

	drawTitleAndInstructions(renderer, paused);
}