#include <SDL.h>
#include <SDL_ttf.h>

#include "size_settings.h"
#include "input_handler.h"
#include "renderer.h"
#include "simulation.h"

bool grid[GRID_WIDTH][GRID_HEIGHT];

// FPS
int fps = 16;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO); // Initialize SDL2
	TTF_Init(); // Initialize TTF

	SDL_Window* window;
	SDL_Renderer* sdl_renderer;

	InputHandler inputHandler;
	Renderer renderer;
	Simulation simulation;

	simulation.initGrid(grid);

	// Create application window
	window = SDL_CreateWindow("Game of Life",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH,
		WINDOW_HEIGHT,
		0);

	// Create SDL Renderer
	sdl_renderer = SDL_CreateRenderer(window, -1, 0);

	// Game loop
	bool running = true;
	bool paused = false;

	SDL_Event event;
	Uint32 frameStart;
	int frameTime;

	int frameDelay = 1000 / fps;

	renderer.changeCursor(false);
	int frameUpdate = 0;
	int lastFrameTime = 0;

	while (running) {
		frameStart = SDL_GetTicks();

		while (SDL_PollEvent(&event)) {
			inputHandler.handleInput(event, grid, running, paused, fps, frameDelay, renderer);
		}

		if (!paused) { // do not run simulation
			simulation.updateGrid(grid);
		}

		SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);
		SDL_RenderClear(sdl_renderer);
		renderer.renderGrid(sdl_renderer, grid, paused, fps);

		frameTime = SDL_GetTicks() - frameStart;

		frameUpdate++;
		if (frameUpdate == 3 || lastFrameTime == 0) {
			lastFrameTime = frameTime;
			frameUpdate = 0;
		}

		renderer.drawFPS(sdl_renderer, paused, lastFrameTime, fps);

 		SDL_RenderPresent(sdl_renderer);

		if (fps > 0 && frameDelay > frameTime && !paused) {
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