#pragma once
#include <cursesw.h>
#include <unordered_map>

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
	Direction get_direction(bool debounce_prev = false);

private:
	typedef std::unordered_map<int, bool> keymap_t;

	// Input buffer holding keypresses for the current frame
	keymap_t keys;		
	// Input buffer holding keypresses for the previous frame
	keymap_t keys_prev;


	WINDOW *win;
};
