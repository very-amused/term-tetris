#include <algorithm>

#include "collision.hpp"

CollisionState::CollisionState(int height, int width) {
	this->height = height;
	this->width = width;
	reset();
}

inline long CollisionState::index(int y, int x) const {
	return (width * y) + x;
}

bool CollisionState::collides(Movement &m) const {
	auto &result = m.result();

	// If any cells would be moved into an already full cell,
	// a collision would occur, making the movement invalid
	for (const auto p : result) {
		if (get_cell(p.y, p.x)) {
			return true;
		}
	}

	return false;
}

inline bool CollisionState::get_cell(int y, int x) const {
	return state[index(y, x)];
}

bool CollisionState::reset_cell(int y, int x) {
	long i = index(y, x);
	if (i >= state.size()) {
		return false;
	}

	state[i] = false;

	return true;
}

bool CollisionState::reset_row(int y) {
	using std::fill_n;

	long start = index(y, 0);
	if (start + width > state.size()) {
		return false;
	}

	fill_n(state, width, false);

	return true;
}

void CollisionState::reset() {
	using std::fill_n;

	state.clear();
	state.resize(height * width, false);
}
