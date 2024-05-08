#include <cursesw.h>

#include "../../game/block.hpp"
#include "grid.hpp"
#include "../../ui.hpp"

using std::unique_ptr;

GameGrid::GameGrid(WINDOW *parent, int h_blocks, int w_blocks, int y, int x) {
	this->parent = parent;
	// Scale h/w
	int h = h_blocks * BLOCK_HEIGHT;
	int w = w_blocks * BLOCK_WIDTH;

	// Create window
	win = newwin(h, w, y, x);
}

void GameGrid::draw(const unique_ptr<GameState> &state) {
	draw_border_light(win);
	wgetch(win);
	// TODO		
}

const int GameGrid::height_blocks() const {
	return height_lines() / BLOCK_HEIGHT;
}
const int GameGrid::width_blocks() const {
	return width_cols() / BLOCK_WIDTH;
}

const int GameGrid::height_lines() const {
	return getmaxy(win);
}
const int GameGrid::width_cols() const {
	return getmaxx(win);
}
