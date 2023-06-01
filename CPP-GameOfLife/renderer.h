#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <vector>

class Renderer {
public:
	void renderGrid(SDL_Renderer* renderer, const std::vector<std::vector<bool>>& grid);
};

#endif