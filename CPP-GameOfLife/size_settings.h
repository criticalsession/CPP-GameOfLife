#ifndef SIZE_SETTINGS_H
#define SIZE_SETTINGS_H

// Width and height of container
const int TOP_PADDING = 100;
const int BOTTOM_PADDING = 50;

const int WIDTH = 1280;
const int WINDOW_HEIGHT = 960;
const int HEIGHT = WINDOW_HEIGHT - TOP_PADDING - BOTTOM_PADDING;

// Width and height of cells
const int CELL_WIDTH = 10;
const int CELL_HEIGHT = 10;

const int GRID_WIDTH = WIDTH / CELL_WIDTH;
const int GRID_HEIGHT = HEIGHT / CELL_HEIGHT;

#endif
