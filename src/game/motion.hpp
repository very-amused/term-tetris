#pragma once
enum struct Direction {
	Up,
	Down,
	Left,
	Right
};

// A unit vector movement from (x, y) in direction d
struct Movement {
	int oy, ox;
	Direction d;
};
