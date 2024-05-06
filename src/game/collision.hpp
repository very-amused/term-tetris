#pragma once
#include <vector>

#include "motion.hpp"

// 2D grid collision state.
struct CollisionState {
	// Initialize collision state for a HxW grid
	CollisionState(int height, int width);

public:
	// Returns whether a movement would cause a collision (overlap/OOB).
	// If the movement would cause a collision, it must be considered *invalid* and not performed.
	bool collides(Movement m) const;

	// Returns whether the cell at (x, y) is full.
	bool get_cell(int y, int x) const;

	// Updates collision state to reflect a movement. Returns false if a collision occured.
	//
	// NOTE: To keep state accurate, this function must perform movements which cause collisions and introduce clipping/OOB.
	// To prevent collisions, ensure that [collides(m)] == false *before* performing any movement
	bool apply_movement(Movement m);

	// Set cell (x, y) to solid. Returns false if collision occured.
	bool fill_cell(int y, int x);

	// Clear cell (x, y). Returns false if collision occured.
	bool clear_cell(int y, int x);
	// Clear row y, returns false if collision occured
	bool clear_row(int y);

private:
	// Height + width in # of BlockCells
	int height, width;

	// 0 if a cell is empty, 1 if it's full
	std::vector<bool> state;

	// Whether an overlap clip has occured (debugging purposes)
	bool has_overlap;
	// Whether an OOB clip has occured
	bool has_oob;
};
