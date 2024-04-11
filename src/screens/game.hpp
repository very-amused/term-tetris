#pragma once
#include <cursesw.h>
#include "../screens.hpp"

struct GameScreen {
	GameScreen();
	~GameScreen();
	GameScreen(const GameScreen &) = delete;

public:
	// Show the game screen and wait until the user chooses to exit
	// (either to main menu or quitting the program entirely)
	void show(Screen &screen);

private:
	WINDOW *win;
};
