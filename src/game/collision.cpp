#include <stdlib.h>

#include "collision.hpp"
#include "../screens/game/grid.hpp"

CollisionState::CollisionState(int height, int width) {
	this->height = height;
	this->width = width;
	reset();
}

inline long CollisionState::index(int y, int x) const {
	return (width * (y + GameGrid::OVERHEAD_ROWS)) + x;
}

bool CollisionState::apply_movement(Movement &m) {
	const bool c = collides(m);

	for (auto p : m.origins) {
		reset_block(p.y, p.x);
	}
	for (auto p : m.result()) {
		fill_block(p.y, p.x);
	}

	return c;
}

bool CollisionState::collides(Movement &m) const {
	auto &result = m.result();

	// If any blocks would be moved into an already full block,
	// a collision would occur, making the movement invalid
	for (const auto p : result) {
		if (get_block(p.y, p.x)) {
			return true;
		}
	}

	return false;
}

bool CollisionState::get_block(int y, int x) const {
	auto i = index(y, x);
	return i >= state.size() ? true : state[index(y, x)]; // Anything OOB causes collision
}

bool CollisionState::fill_block(int y, int x) {
	const bool c = get_block(y, x);
	auto i = index(y, x);
	if (i >= state.size()) {
		return false;
	}

	state[i] = true;

	return c;
}


bool CollisionState::reset_block(int y, int x) {
	auto i = index(y, x);
	if (i >= state.size()) {
		return false;
	}

	state[i] = false;

	return true;
}

bool CollisionState::reset_row(int y) {
	long start = index(y, 0);
	if (start + width > state.size()) {
		return false;
	}

	for (size_t i = start; i < width; i++) {
		state[i] = false;
	}

	return true;
}

void CollisionState::reset() {
	state.clear();
	state.resize(height * width, false);
}
