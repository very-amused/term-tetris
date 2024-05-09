#pragma once
#include <vector>

// A translational movement direction
enum struct Direction {
	None,
	Down,
	Left,
	Right
};

struct Point { int y, x; };

// A unit vector motion from a set of origin points
struct Movement {
	// A vector containing one or more (y, x) origin points
	std::vector<Point> origins;
	Direction d;

	// Get a vector of points describing the results of applying the movement
	// to each origin point
	const std::vector<Point> &result();

	// Apply the movement to its origin points.
	// Multiple calls can be used for iterative motion.
	void apply();

private:
	std::vector<Point> result_points; // memoize result points
	void calculate_results();
};
