#include <memory>
#include <cursesw.h>

#include "row.hpp"
#include "collision.hpp"

using std::unique_ptr;

BlockRow::BlockRow(WINDOW *parent, int w_blocks, int y) {
	this->y = y;
	int h = BLOCK_HEIGHT;
	int w = w_blocks * BLOCK_WIDTH;

	// Scale and account for grid border
	int y_col = 1 + (y * BLOCK_HEIGHT);
	int x = 1;

	win = derwin(parent, h, w, y, x);
	block_wins.resize(w_blocks, NULL);
}
