#include <SDL.h>
#include <vector>

using std::vector;

// Width and height of container
const int WIDTH = 800;
const int HEIGHT = 600;

// Width and height of cells
const int CELL_WIDTH = 10;
const int CELL_HEIGHT = 10;

const int GRID_WIDTH = WIDTH / CELL_WIDTH;
const int GRID_HEIGHT = HEIGHT / CELL_HEIGHT;

// Vector grid
vector<vector<bool>> grid(GRID_WIDTH, vector<bool>(GRID_HEIGHT, false));

int getLiveNeighbours(int x, int y) {
	int liveNeighbours = 0;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0) continue;

			int nx = x + i;
			int ny = y + j;
			if (nx >= 0 && ny >= 0 && nx < GRID_WIDTH && ny < GRID_HEIGHT && grid[nx][ny]) {
				liveNeighbours++;
			}
		}
	}

	return liveNeighbours;
}

void updateGrid() {
	vector<vector<bool>> newGrid = grid;
	for (int x = 0; x < GRID_WIDTH; x++) {
		for (int y = 0; y < GRID_HEIGHT; y++) {
			int liveNeighbours = getLiveNeighbours(x, y);
			if (grid[x][y]) { // already alive
				if (liveNeighbours < 2 || liveNeighbours > 3) {
					newGrid[x][y] = false; // cell died
				}
			}
			else {
				if (liveNeighbours == 3) {
					newGrid[x][y] = true; // cell becomes alive
				}
			}
		}
	}

	grid = newGrid;
}

void renderGrid(SDL_Renderer *renderer) {
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

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO); // Initialize SDL2

	SDL_Window* window;
	SDL_Renderer* renderer;

	// Create application window
	window = SDL_CreateWindow("Game of Life",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH,
		HEIGHT,
		0);

	// Create SDL Renderer
	renderer = SDL_CreateRenderer(window, -1, 0);

	// Game loop
	bool running = true;
	SDL_Event event;
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
			
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				int x, y;
				SDL_GetMouseState(&x, &y);

				int gridX = x / CELL_WIDTH;
				int gridY = y / CELL_HEIGHT;

				grid[gridX][gridY] = !grid[gridX][gridY];
			}
		}

		updateGrid();
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		renderGrid(renderer);
		SDL_RenderPresent(renderer);
		SDL_Delay(100);
	}

	// Clean up
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}