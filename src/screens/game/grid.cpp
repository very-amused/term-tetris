#include <cursesw.h>

#include "../../game/block.hpp"
#include "grid.hpp"
#include "../../ui.hpp"

using std::unique_ptr;

GameGrid::GameGrid(WINDOW *parent, int h_blocks, int w_blocks, int y, int x) {
	this->parent = parent;
	// Scale h/w and account for border
	int h = (h_blocks * BLOCK_HEIGHT) + 2;
	int w = (w_blocks * BLOCK_WIDTH) + 2;

	// Create window
	win = newwin(h, w, y, x);
	if (!win) {
		printf("Panic!!!!\n");
	}
}

void GameGrid::draw(const unique_ptr<GameState> &state) {
	draw_border_light(win);
	swrefresh(parent, win);

	state->current_ttm->draw();
}

const int GameGrid::offset_y() const {
	return getbegy(win);
}
const int GameGrid::offset_x() const {
	return getbegx(win);
}
const int GameGrid::end_y() const {
	return getmaxy(win) - 1;
}
const int GameGrid::end_x() const {
	return getmaxx(win) - 1;
}

const int GameGrid::height_lines() const {
	return end_y() - offset_y();
}
const int GameGrid::width_cols() const {
	return getmaxx(win);
}

const int GameGrid::height_blocks() const {
	return height_lines() / BLOCK_HEIGHT;
}
const int GameGrid::width_blocks() const {
	return width_cols() / BLOCK_WIDTH;
}

