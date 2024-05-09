#include <cursesw.h>

#include "input.hpp"
#include "motion.hpp"
#include "../keybinds.hpp"

struct DirectionInput {
	int key;
	Direction d;
};

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
	// Move previous frame's keypresses, clear for current frame
	keys_prev = std::move(keys);
	keys.clear();

	// Store which keys are pressed in the current frame
	int key;
	while (key = wgetch(win), key != ERR) {
		keys[key] = true;
	}
}


Direction GameInput::get_direction(bool debounce_prev) {
	// Prioritize soft-drop input when checking directions
	static const DirectionInput check_directions[] = {
		{DOWN, Direction::Down},
		{LEFT, Direction::Left},
		{RIGHT, Direction::Right}
	};
	static const size_t check_directions_len = sizeof(check_directions) / sizeof(check_directions[0]);

	for (size_t i = 0; i < check_directions_len; i++) {
		auto input = check_directions[i];
		if (keys[input.key] &&
				(!debounce_prev || !keys_prev[input.key])) {
			return input.d;
		}
	}

	return Direction::None;
}
