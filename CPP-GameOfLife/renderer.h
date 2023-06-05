#ifndef RENDERER_H
#define RENDERER_H

#include "size_settings.h"
#include <SDL.h>
#include <string>

class Renderer {
public:
	void renderGrid(SDL_Renderer* renderer, const bool(&grid)[GRID_WIDTH][GRID_HEIGHT], bool paused, int fps);
	void drawText(SDL_Renderer* renderer, const std::string& text, int x, int y, int fontSize);
	void drawText(SDL_Renderer* renderer, const std::string& text, int x, int y, int fontSize, SDL_Color color);
	void changeCursor(bool toCrosshair);
	void drawFPS(SDL_Renderer* renderer, bool paused, int frameTime, int fps);
private:
	void drawTitleAndInstructions(SDL_Renderer* renderer, bool paused, int fps);
	void renderBorders(SDL_Renderer* renderer);
};

#endif