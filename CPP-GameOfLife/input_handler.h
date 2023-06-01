#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL.h>
#include <vector>

class InputHandler {
public:
	void handleInput(SDL_Event& event, std::vector<std::vector<bool>>& grid, bool& running, bool& paused);
private:
	void flipCell(int x, int y, std::vector<std::vector<bool>>& grid);
};

#endif