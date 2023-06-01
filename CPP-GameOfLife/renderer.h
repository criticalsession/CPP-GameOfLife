#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <vector>
#include <string>

class Renderer {
public:
	void renderGrid(SDL_Renderer* renderer, const std::vector<std::vector<bool>>& grid, bool paused, int fps);
	void drawText(SDL_Renderer* renderer, const std::string& text, int x, int y, int fontSize);
private:
	void drawTitleAndInstructions(SDL_Renderer* renderer, bool paused, int fps);
	void renderBorders(SDL_Renderer* renderer);
};

#endif