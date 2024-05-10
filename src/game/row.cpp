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
	
}

void BlockRow::draw() {
	const int y_minrow = grid->offset_y() + y * BLOCK_HEIGHT;
	const int y_maxrow = y_minrow + BLOCK_HEIGHT - 1;
	for (auto &b: blocks) {
		if (!b.solid) {
			continue;
		}
		b.draw();
	}


}
