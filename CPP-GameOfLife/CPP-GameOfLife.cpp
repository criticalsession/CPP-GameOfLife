#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

#include "size_settings.h"
#include "renderer.h"
#include "input_handler.h"
#include "simulation.h"

using std::vector;

// Vector grid
vector<vector<bool>> grid(GRID_WIDTH, vector<bool>(GRID_HEIGHT, false));

// FPS
const int FPS = 16;
const int frameDelay = 1000 / FPS;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO); // Initialize SDL2
	TTF_Init(); // Initialize TTF

	SDL_Window* window;
	SDL_Renderer* sdl_renderer;

	InputHandler inputHandler;
	Renderer renderer;
	Simulation simulation;

	// Create application window
	window = SDL_CreateWindow("Game of Life",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH,
		HEIGHT,
		0);

	// Create SDL Renderer
	sdl_renderer = SDL_CreateRenderer(window, -1, 0);

	// Game loop
	bool running = true;
	bool paused = false;

	SDL_Event event;
	Uint32 frameStart;
	int frameTime;
	while (running) {
		frameStart = SDL_GetTicks();

		while (SDL_PollEvent(&event)) {
			inputHandler.handleInput(event, grid, running, paused);
		}

		if (!paused) { // do not run simulation
			simulation.updateGrid(grid);
		}

		SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);
		SDL_RenderClear(sdl_renderer);
		renderer.renderGrid(sdl_renderer, grid, paused);
		SDL_RenderPresent(sdl_renderer);
		
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	// Clean up
	SDL_DestroyRenderer(sdl_renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	TTF_Quit();

	return 0;
}