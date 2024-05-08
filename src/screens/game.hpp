#pragma once
#include <memory>

#include "../game/clock.hpp"
#include "../game/state.hpp"
#include "../screens.hpp"
#include "game/grid.hpp"

struct GameScreen {
	GameScreen();
	~GameScreen();
	GameScreen(const GameScreen &) = delete;

public:
	// Show the game screen and start the gameplay loop until the user dies or exits
	// (no clue if 'dies' is the right term here)
	void play(Screen &screen);
	
private:
	WINDOW *win;
	// Internal game state
	std::unique_ptr<GameState> state;
	// Fixed-rate clock that manages input and state each frame
	std::unique_ptr<GameClock> clock;

	// Grid where blocks are placed (main gameplay area)
	std::unique_ptr<GameGrid> grid;
};
