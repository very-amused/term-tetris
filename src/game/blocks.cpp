#include <algorithm>

#include "blocks.hpp"
#include "motion.hpp"

BlockCell::BlockCell(WINDOW *block, int y, int x) {
	is_solid = true;
	// Create derived window if the block is solid
	win = derwin(block, WIDTH, HEIGHT, y * HEIGHT, x * WIDTH);
}

BlockCell::BlockCell() {
	is_solid = false;
	win = NULL;
}

Block::Block(const BlockTemplate t) {
	// Create cell windows
	for (size_t row = 0; row < 2; row++) {
		for (size_t col = 0; col < 2; col++) {
			cells[row][col] = t[row][col] ? BlockCell(win, row, col) : BlockCell();
		}
	}
}

bool Block::move(Direction d) {
	// Only upwards movement is valid
	if (d == Direction::Up) {
		return false;
	}

	// Create movement struct
	Movement move;
	move.d = d;
	// TODO
	return false;
}
