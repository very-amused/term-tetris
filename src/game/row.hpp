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
	// Create an empty block row starting at (y, 0) block coords
	BlockRow(WINDOW *parent, int w_blocks, int y);
	~BlockRow() = default;

public:
	// Set the entire row's state from collision, returning false if
	// the y coordinate is OOB
	bool set_row(const std::unique_ptr<CollisionState> &collision);

	void draw();


private:
	int y;
	// Placed rows are drawn *before* the active TTM on the grid
	WINDOW *win;
	// Derived block windows intersecting the active TTM are drawn *after*
	std::vector<WINDOW *> block_wins;
};
