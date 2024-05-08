#include <algorithm>

#include "ttm.hpp"
#include "motion.hpp"
#include "collision.hpp"
#include "../ui.hpp"
#include "../screens/game/grid.hpp"

TTM::TTM(const TTMtemplate t) {
	pad = NULL;
	// Create block pad windows
	for (size_t row = 0; row < 2; row++) {
		for (size_t col = 0; col < 4; col++) {
			blocks[row][col] = Block(t[row][col]);
		}
	}
}

TTM::~TTM() {
	delwin(pad);
}

const int TTM::collision_y() const {
	int y = 0;		

	for (size_t row = 0; row < 4; row++) {
		bool empty = true;
		for (size_t col = 0; col < 4; col++) {
			if (blocks[row][col].solid) {
				y++;
				empty = false;
				break;
			}
		}
		if (empty) {
			break;
		}
	}

	return y;
}

const int TTM::collision_x() const {
	using std::max;

	int x = 0;

	for (size_t row = 0; row < collision_y(); row++) {
		int x_local = 0;
		for (size_t col = 0; col < 4; col++) {
			if (!blocks[row][col].solid) {
				break;
			}
			x_local++;
		}
		x = max(x, x_local);
	}

	return x;
}

void TTM::attach(const GameGrid *grid) {
	this->grid = grid;
	// Create 4x4 pad
	pad = newpad(4 * BLOCK_HEIGHT, 4 * BLOCK_WIDTH);
	// Start at center, directly above grid
	x = grid->offset_x() + (x_centered(grid->width_cols()) / BLOCK_WIDTH);
}

bool TTM::move(Direction d, CollisionState &collision) {
	// Create movement struct
	Movement move;
	move.d = d;

	// TODO

	return false;
}

bool TTM::rotate(CollisionState &collision) {
	// TODO
	return false;
}
