#pragma once
#include <cursesw.h>
#include <memory>

#include "../../game/state.hpp"

// The block grid where gameplay takes place
struct GameGrid {
	// x and y are in cells, not cols/rows
	GameGrid(WINDOW *parent, int y, int x);
	~GameGrid() = default;
	GameGrid(const GameGrid &) = delete;

public:

private:
	WINDOW *win;
	std::unique_ptr<GameState> game_state;
};
