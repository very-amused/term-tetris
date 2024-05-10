#include <algorithm>
#include <memory>
#include <cursesw.h>

#include "row.hpp"
#include "../screens/game/grid.hpp"
#include "block.hpp"

using std::unique_ptr;

BlockRow::BlockRow(const GameGrid *grid, int y) {
	this->grid = grid;
	this->y = y;
	// Create a BLOCK_HEIGHT * grid len pad
	pad = newpad(BLOCK_HEIGHT, grid->width_cols());
	blocks.resize(grid->width_cols());
}

BlockRow::~BlockRow() {
	delwin(pad);
}

void BlockRow::push_block(Block block, int x) {
	blocks[x] = std::move(block);

	blocks[x].reattach(pad, 0, x);
}

void BlockRow::draw() {
	using std::max;

	const int y_minrow = grid->offset_y() + (y * BLOCK_HEIGHT); // prevent ARE clipping
	const int x_mincol = grid->offset_x();

	for (size_t x = 0; x < blocks.size(); x++) {
		auto &b = blocks[x];
		if (!b.solid) {
			continue;
		}
		b.draw();

		b.refresh(y_minrow, x_mincol, 0, x);
	}
}
