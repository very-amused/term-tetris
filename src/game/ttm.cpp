#include "ttm.hpp"
#include "motion.hpp"

Block::Block(WINDOW *block, int y, int x) {
	is_solid = true;
	// Create derived window if the block is solid
	win = derwin(block, TTM_WIDTH, TTM_HEIGHT, y * TTM_HEIGHT, x * TTM_WIDTH);
}

Block::Block() {
	is_solid = false;
	win = NULL;
}

TTM::TTM(const TTMtemplate t) {
	// Create block windows
	for (size_t row = 0; row < 2; row++) {
		for (size_t col = 0; col < 2; col++) {
			blocks[row][col] = t[row][col] ? Block(win, row, col) : Block();
		}
	}
}

bool TTM::move(Direction d) {
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
