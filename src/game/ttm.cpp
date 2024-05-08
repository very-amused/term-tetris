#include "ttm.hpp"
#include "motion.hpp"

TTM::TTM(const TTMtemplate t) {
	// Create block pad windows
	for (size_t row = 0; row < 2; row++) {
		for (size_t col = 0; col < 4; col++) {
			blocks[row][col] = Block(t[row][col]);
		}
	}
}

void TTM::attach(const WINDOW *grid) {
	this->grid = grid;
	// Create pad
}

void TTM::move(Direction d) {
	// Create movement struct
	Movement move;
	move.d = d;
}

