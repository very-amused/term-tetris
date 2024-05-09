#include <cursesw.h>
#include <algorithm>

#include "input.hpp"
#include "motion.hpp"
#include "../keybinds.hpp"

GameInput::GameInput(WINDOW *win) {
	this->win = win;
	// Disable input blocking	
	// ref https://stackoverflow.com/a/48086782
	nodelay(win, true);
}

GameInput::~GameInput() {
	// Re-enable input blocking
	nodelay(win, false);
}

void GameInput::getkeys() {
	// Flush old input
	keys.clear();

	// Store which keys are pressed in the current frame
	int key;
	while (key = wgetch(win), key != ERR) {
		keys[key] = true;
	}
}

struct DirectionInput {
	int key;
	Direction d;
};

Direction GameInput::get_direction() {
	// Prioritize soft-drop input when checking directions
	static const DirectionInput check_directions[] = {
		{DOWN, Direction::Down},
		{LEFT, Direction::Left},
		{RIGHT, Direction::Right}
	};
	static const size_t check_directions_len = sizeof(check_directions) / sizeof(check_directions[0]);

	for (size_t i = 0; i < check_directions_len; i++) {
		auto input = check_directions[i];
		if (keys[input.key]) {
			return input.d;
		}
	}

	return Direction::None;
}
