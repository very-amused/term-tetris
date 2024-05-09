#include <stdlib.h>

#include "collision.hpp"
#include <vector>

using std::vector;

CollisionState::CollisionState(int height, int width) {
	this->height = height + 2;
	this->width = width;
	reset();
}

inline long CollisionState::index(int y, int x) const {
	if (x < 0 || x >= width) {
		return -1;
	}

	y += 2;
	if (y < 0 || x >= height) {
		return -1;
	}

	return (width * y) + x;
}
inline bool CollisionState::valid_index(long i) const {
	return i >= 0 && i < state.size();
}

bool CollisionState::collides(Movement &m) {
	// If any blocks would be moved into an already full block,
	// a collision would occur, making the movement invalid

	// Temporarily clear origin points
	for (const auto p : m.origins) {
		reset_block(p.y, p.x);
	}

	bool c = false;
	for (const auto p : m.result()) {
		if (get_block(p.y, p.x)) {
			c = true;
			break;
		}
	}

	// Restore origin points
	for (const auto p : m.origins) {
		fill_block(p.y, p.x);
	}

	return c;
}

bool CollisionState::get_block(int y, int x) const {
	auto i = index(y, x);
	return valid_index(i) ? state[i] : true; // OOB must always cause collision
}

vector<bool> CollisionState::get_row(int y) {
	vector<bool> row;

	// Validate y as a row start index
	if (y % width != 0) {
		return row;
	}
	auto start = index(y, 0), end = index(y, width);
	if (!(valid_index(start) && valid_index(end - 1)))  {
		return row;
	}

	row.reserve(width);
	for (size_t i = start; i < end; i++) {
		row.push_back(state[i]);
	}

	return row;
}

bool CollisionState::apply_movement(Movement &m) {
	bool c = collides(m);

	for (auto p : m.origins) {
		reset_block(p.y, p.x);
	}
	for (auto p : m.result()) {
		fill_block(p.y, p.x);
	}

	return !c;
}

bool CollisionState::fill_block(int y, int x) {
	auto i = index(y, x);
	if (!valid_index(i)) {
		return false;
	}
	const bool c = state[i];
	state[i] = true;

	return true;
}

bool CollisionState::reset_block(int y, int x) {
	long i = index(y, x);
	if (!valid_index(i)) {
		return false;
	}

	state[i] = false;

	return true;
}

bool CollisionState::reset_row(int y) {
	long start = index(y, 0);
	if (!valid_index(start) || start + width > state.size()) {
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
