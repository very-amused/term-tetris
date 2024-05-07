#include "grid.hpp"
#include "../../game/blocks.hpp"

GameGrid::GameGrid(WINDOW *parent, int h_cells, int w_cells, int y, int x) {
	// Scale h/w
	int h = h_cells * BlockCell::HEIGHT;
	int w = w_cells * BlockCell::WIDTH;

	// Create window
	win = newwin(h, w, y, x);
}
