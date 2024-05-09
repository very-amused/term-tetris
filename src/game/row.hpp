#pragma once
#include <cursesw.h>
#include <vector>
#include <memory>

#include "block.hpp"
#include "collision.hpp"

// A row with one or more placed blocks
//
// In order to achieve correct rendering behavior
// and row clearing logic, it's necessary to decouple TTM blocks from their parent Tetrominos
// (and the associated TTM collision box) once they are at rest.
struct BlockRow {
	// Create an empty block row at the given (y, x) origin *screen* coordinates
	BlockRow(int w_blocks, int screen_y, int screen_x);
	~BlockRow();

public:
	// Clear the block row
	void clear();

	// Set the entire row's state from collision, returning false if
	// the y coordinate is OOB
	bool set_row(const std::unique_ptr<CollisionState> &);



private:
	// The parent row pad is drawn first on the grid, before the active TTM
	WINDOW *pad;
	// The child block pads are used to redraw blocks which overlap with the active TTM's
	// collision box, *after* the active TTM is drawn
	std::vector<WINDOW *> block_pads;
};
