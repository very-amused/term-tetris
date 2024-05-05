#pragma once
#include <memory>

#include "../screens.hpp"
#include "game/grid.hpp"

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
	std::unique_ptr<GameGrid> grid;
};
