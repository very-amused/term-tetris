#pragma once
#include <cursesw.h>

#include "../DB.hpp"
#include "../screens.hpp"

struct ScoreboardScreen {
	ScoreboardScreen();
	~ScoreboardScreen();
	ScoreboardScreen(const ScoreboardScreen &) = delete;

public:
	// Show the scoreboard screen until the user has exited
	void show(Screen &screen);

private:
	WINDOW *win;
};
