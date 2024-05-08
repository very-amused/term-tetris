#pragma once
#include <vector>

#include "motion.hpp"

// 2D grid collision state.
struct CollisionState {
	// Initialize collision state for a HxW grid
	CollisionState(int h_blocks, int w_blocks);

public:
	// Returns whether 1 or more movements would cause a collision (overlap/OOB).
	// If a collision would result, the entire set of movements must be considered *invalid* and not performed.
	bool collides(Movement &m) const;

	// Returns whether the cell at (x, y) is full.
	bool get_cell(int y, int x) const;

	// Updates collision state and movement points to reflect a movement. Returns false if a collision occured.
	//
	// NOTE: To keep state accurate, this function must perform movements which cause collisions and introduce clipping/OOB.
	// To prevent collisions, ensure that [collides(m)] == false *before* performing any movement
	bool apply_movement(Movement &m);

	// Set cell (x, y) to solid. Returns false if collision occured.
	bool fill_cell(int y, int x);

	// Reset cell (x, y). Returns false if cell is OOB.
	bool reset_cell(int y, int x);
	// Reset row y, returns false if row is OOB.
	bool reset_row(int y);
	// Reset the whole grid, respecting the currently set dimensions
	void reset();

private:
	// Height + width in # of BlockCells
	int height, width;

	// 0 if a cell is empty, 1 if it's full
	std::vector<bool> state;

	long index(int y, int x) const;

	// Whether an overlap clip has occured (debugging purposes)
	bool has_overlap;
	// Whether an OOB clip has occured
	bool has_oob;
};
