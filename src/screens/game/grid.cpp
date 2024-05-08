#include "../../game/ttm.hpp"
#include "grid.hpp"
#include "../../ui.hpp"

using std::unique_ptr;

GameGrid::GameGrid(WINDOW *parent, int h_blocks, int w_blocks, int y, int x) {
	this->parent = parent;
	// Scale h/w
	int h = h_blocks * TTM_HEIGHT;
	int w = w_blocks * TTM_WIDTH;

	// Create window
	win = newwin(h, w, y, x);
}

void GameGrid::draw(const unique_ptr<GameState> &state) {
	draw_border_light(win);
	wgetch(win);
	// TODO		
}
