#include <algorithm>
#include <cursesw.h>

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
			blocks[row][col] = Block(t.blocks[row][col]);
		}
	}
}

TTM::~TTM() {
	delwin(pad);
}

const int TTM::collision_y() const {
	int y = 0;

	for (int row = 0; row < 4; row++) {
		bool empty = true;
		for (int col = y; col < 4; col++) {
			if (blocks[row][col].solid) {
				y++;
				empty = false;
				break;
			}
		}
		// Stop detection early when we find a blank row
		if (empty) {
			break;
		}
	}

	return y;
}

const int TTM::collision_x() const {
	int x = 0;

	for (int row = 0; row < collision_y(); row++) {
		if (x == 4) {
			break;
		}

		for (int col = x; col < 4; col++) {
			if (blocks[row][col].solid) {
				x = col + 1;
			}
		}
	}

	return x;
}

void TTM::attach(const GameGrid *grid) {
	this->grid = grid;
	// Create 4x4 pad
	pad = newpad(4 * BLOCK_HEIGHT, 4 * BLOCK_WIDTH);
	// Start at center, directly above grid
	x =  wx_centered(grid->width_cols(), getmaxx(pad)) / BLOCK_WIDTH;
	y = -collision_y();

	// Attach blocks
	for (int row = 0; row < collision_y(); row++) {
		for (int col = 0; col < collision_x(); col++) {
			blocks[row][col].attach(pad, row, col);
		}
	}
}

bool TTM::attached() {
	return pad && grid;
}

void TTM::draw() {
	using std::max;

	// Calcualte absolute x/y in screen units
#define ARE_DEBUG 1
#if ARE_DEBUG
	const int y_minrow = grid->offset_y() + (y * BLOCK_HEIGHT);
#else
	const int y_minrow = grid->offset_y() + max(y * BLOCK_HEIGHT, 0); // prevent ARE clipping
#endif
#undef ARE_DEBUG
	//printf("%d + %d\n", grid->offset_x(), x * BLOCK_WIDTH);
	const int x_mincol = grid->offset_x() + (x * BLOCK_WIDTH);
	// Calcualte absolute x/y end coords in screen units
	const int y_maxrow = grid->offset_y() + ((y + collision_y()) * BLOCK_HEIGHT);
	const int x_maxcol = grid->offset_x() + ((x + collision_x()) * BLOCK_WIDTH);

	// Use prefresh to render
	//draw_border_light(pad); // FIXME: debug
	for (auto &row : blocks) {
		for (auto &blk : row) {
			blk.draw();
		}
	}
	prefresh(pad, 0, 0,
			y_minrow, x_mincol, y_maxrow, x_maxcol);
}

bool TTM::move(Direction d, CollisionState &collision) {
	// Create movement struct
	Movement move;
	move.d = d;
	// Append origin vec

	// TODO

	return false;
}

bool TTM::rotate(CollisionState &collision) {
	// TODO
	return false;
}
