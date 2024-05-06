#include "collision.hpp"
#include "blocks.hpp"

CollisionState::CollisionState(int height, int width) {
	this->height = height;
	this->width = width;
	state.resize(height * width, false);
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
