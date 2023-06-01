#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL.h>
#include <vector>
#include "renderer.h"

using std::vector;

class InputHandler {
public:
	void handleInput(SDL_Event& event, vector<vector<bool>>& grid, bool& running, bool& paused, int& fps, int& frameDelay, Renderer& renderer);
private:
	void flipCell(int x, int y, std::vector<std::vector<bool>>& grid);
};

#endif