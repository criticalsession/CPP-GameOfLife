#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL.h>
#include "renderer.h"
#include "size_settings.h"

class InputHandler {
public:
	void handleInput(SDL_Event& event, bool(&grid)[GRID_WIDTH][GRID_HEIGHT], bool& running, bool& paused, int& fps, int& frameDelay, Renderer& renderer);
private:
	void flipCell(int x, int y, bool(&grid)[GRID_WIDTH][GRID_HEIGHT]);
};

#endif