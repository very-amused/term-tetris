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
	pad = newpad(BLOCK_HEIGHT, grid->height_lines());
}

BlockRow::~BlockRow() {
	delwin(pad);
}

void BlockRow::push_block(Block block, int x) {
	blocks[x] = std::move(block);

	block.reattach(pad, 0, x);
}

void BlockRow::draw() {
	using std::max;

	const int y_minrow = grid->offset_y() + max(y * BLOCK_HEIGHT, 0); // prevent ARE clipping
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
