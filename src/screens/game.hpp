#pragma once
#include <memory>

#include "../screens.hpp"
#include "game/grid.hpp"

struct GameScreen {
	GameScreen();
	~GameScreen();
	GameScreen(const GameScreen &) = delete;

public:
	// Show the game screen without starting gameplay.
	void show();

	// Start the gameplay loop until the user dies or exits
	// (no clue if 'dies' is the right term here)
	void play();
	
private:
	WINDOW *win;
	// The entirety of game state and logic
	std::unique_ptr<GameState> state;

	// Grid where blocks are placed (main gameplay area)
	std::unique_ptr<GameGrid> grid;
};
