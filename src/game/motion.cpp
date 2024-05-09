#include "motion.hpp"
#include <algorithm>

const std::vector<Point> &Movement::result() {
	calculate_results();
	return result_points;
}

void Movement::apply() {
	using std::swap;
	calculate_results();
	// We use swap instead of move so the result_points vector keeps its reserved capacity after invalidation
	swap(origins, result_points);
	result_points.clear();
}

void Movement::calculate_results() {
	if (!result_points.empty()) {
		return;
	}

	result_points = origins;

	Point inc = {0, 0};
	switch (d) {
	case Direction::None:
		break;
	case Direction::Down:
		inc.y = 1;
		break;
	case Direction::Left:
		inc.x = -1;
		break;
	case Direction::Right:
		inc.x = 1;
	}
	for (auto &p : result_points) {
		p.x += inc.x;
		p.y += inc.y;
	}
}
