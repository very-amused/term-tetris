#include <algorithm>
#include <vector>
#include <memory>
#include <cursesw.h>

#include "ttm.hpp"
#include "motion.hpp"
#include "collision.hpp"
#include "../ui.hpp"
#include "../screens/game/grid.hpp"

using std::unique_ptr;

TTM::TTM(const TTMtemplate t, chtype color) {
	pad = NULL;
	this->color = color;
	// Create block pad windows
	for (size_t row = 0; row < 2; row++) {
		for (size_t col = 0; col < 4; col++) {
			blocks[row][col] = Block(t.blocks[row][col]);
		}
	}
	for (size_t row = 2; row < 4; row++) {
		for (size_t col = 0; col < 4; col++) {
			blocks[row][col] = Block(false);
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
		for (int col = 0; col < 4; col++) {
			if (blocks[row][col].solid) {
				y = row + 1;
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

void TTM::attach(const GameGrid *grid, unique_ptr<CollisionState> &collision) {
	this->grid = grid;
	// Create 4x4 pad
	pad = newpad(4 * BLOCK_HEIGHT, 4 * BLOCK_WIDTH);
	// Start at center, directly above grid
	x =  wx_centered(grid->width_cols(), getmaxx(pad)) / BLOCK_WIDTH;
	y = -collision_y();

	// Attach blocks
	for (int row = 0; row < collision_y(); row++) {
		for (int col = 0; col < collision_x(); col++) {
			auto &b = blocks[row][col];
			if (!b.solid) {
				continue;
			}
			collision->fill_block(y + row, x + col);
			b.color = color;
			b.attach(pad, row, col);
		}
	}
}

bool TTM::attached() {
	return pad && grid;
}

void TTM::draw() {
	using std::max;

	// Calcualte absolute x/y in screen units
#ifdef DEBUG
	const int y_minrow = grid->offset_y() + (y * BLOCK_HEIGHT);
	const int p_minrow = 0;
#else
	const int y_minrow = grid->offset_y() + max(y * BLOCK_HEIGHT, 0); // prevent ARE clipping
	const int p_minrow = max(-y * BLOCK_HEIGHT, 0);
#endif
	//printf("%d + %d\n", grid->offset_x(), x * BLOCK_WIDTH);
	const int x_mincol = grid->offset_x() + (x * BLOCK_WIDTH);
	// Calcualte absolute x/y *inclusive* end coords in screen units
	const int y_maxrow = y_minrow + (collision_y() * BLOCK_HEIGHT) - 1;
	const int x_maxcol = x_mincol + (collision_x() * BLOCK_WIDTH) - 1;

	// Use prefresh to render
	//draw_border_light(pad); // FIXME: debug
	for (size_t row = 0; row < collision_y(); row++) {
		for (size_t col = 0; col < collision_x(); col++) {
			auto &blk = blocks[row][col];
			blk.draw();
		}
	}

	prefresh(pad, p_minrow, 0,
			y_minrow, x_mincol, y_maxrow, x_maxcol);
}

BlockPoints TTM::block_points() {
	BlockPoints points;
	const int collision_area = collision_y() * collision_x();
	points.coords.reserve(collision_area);
	points.blocks.reserve(collision_area);

	for (int row = 0; row < collision_y(); row++) {
		for (int col = 0; col < collision_x(); col++) {
			// Only push coordinates of solid blocks
			if (!blocks[row][col].solid) {
				continue;
			}

			points.coords.push_back({.y = y + row, .x = x + col});
			points.blocks.push_back(&blocks[row][col]);
		}
	}

	return points;
}

bool TTM::move(Direction d, unique_ptr<CollisionState> &collision) {
	// Starting block points/coords
	auto bp_start = block_points();
	// Create movement struct
	Movement move;
	move.d = d;
	move.origins = bp_start.coords;
	if (collision->collides(move)) {
		return false;
	}

	collision->apply_movement(move);
	switch (d) {
	case Direction::None:
		break;
	case Direction::Down:
		y++;
		break;
	case Direction::Left:
		x--;
		break;
	case Direction::Right:
		x++;
	}

	return true;
}

bool TTM::rotate(CollisionState &collision) {
	// TODO
	return false;
}
