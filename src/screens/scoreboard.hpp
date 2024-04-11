#pragma once
#include "../DB.hpp"
#include "../screens.hpp"

#include <cursesw.h>
#include <memory>

struct ScoreboardScreen {
	ScoreboardScreen();
	~ScoreboardScreen();
	ScoreboardScreen(const ScoreboardScreen &) = delete;

public:
	// Show the scoreboard screen until the user has exited
	void show(Screen &screen, std::unique_ptr<DB> &db);

private:
	WINDOW *win;
};
