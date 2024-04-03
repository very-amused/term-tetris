#pragma once

// Ncurses screen state
struct Screen {
	Screen();
	~Screen();
	// Ref jplank
	// We don't want to ever copy our global screen state
	Screen(const Screen &) = delete;
};
