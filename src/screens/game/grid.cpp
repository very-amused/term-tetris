#include "../../game/blocks.hpp"
#include "grid.hpp"
#include "../../ui.hpp"

using std::unique_ptr;

GameGrid::GameGrid(WINDOW *parent, int h_cells, int w_cells, int y, int x) {
	this->parent = parent;
	// Scale h/w
	int h = h_cells * TTM_HEIGHT;
	int w = w_cells * TTM_WIDTH;

	// Create window
	win = newwin(h, w, y, x);
}

void GameGrid::draw(const unique_ptr<GameState> &state) {
	draw_border_light(win);
	wgetch(win);
	// TODO		
}
