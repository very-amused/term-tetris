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
	bool collides(Movement &m);

	// Returns whether the block at (x, y) is full.
	bool get_block(int y, int x) const;

	// Updates collision state and movement points to reflect a movement. Returns false if a collision occured.
	//
	// NOTE: To keep state accurate, this function must perform movements which cause collisions and introduce clipping/OOB.
	// To prevent collisions, ensure that [collides(m)] == false *before* performing any movement
	bool apply_movement(Movement &m);


	// Set block (x, y) to solid. Returns false if collision occured.
	bool fill_block(int y, int x);
	// Reset block (x, y). Returns false if block is OOB.
	bool reset_block(int y, int x);
	// Reset row y, returns false if row is OOB.
	bool reset_row(int y);
	// Reset the whole grid, respecting the currently set dimensions
	void reset();

private:
	// Height + width (blocks)
	int height, width;

	// 0 if a block is empty, 1 if it's full
	std::vector<bool> state;

	long index(int y, int x) const;
	bool valid_index(const long i) const;

	// Whether an overlap clip has occured (debugging purposes)
	bool has_overlap;
	// Whether an OOB clip has occured
	bool has_oob;
};
