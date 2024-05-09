#pragma once
#include <cursesw.h>
#include <unordered_map>
#include <vector>

#include "motion.hpp"

struct GameInput {
	// Configure game window to receive input during gameplay
	GameInput(WINDOW *win);
	GameInput(const GameInput &) = delete;
	~GameInput();

	// Flush and then populate the input buffer for the current frame
	void getkeys();

	// Return the currently active direction input to apply,
	// or Direction::None
	Direction get_direction();

private:
	// Input buffer holding currently pressed keys
	std::unordered_map<int, bool> keys;		

	WINDOW *win;
};
