#pragma once
#include <cursesw.h>

// The block grid where gameplay takes place
struct GameGrid {
	GameGrid(WINDOW *parent);
	~GameGrid() = default;
	GameGrid(const GameGrid &) = delete;

public:

private:
	WINDOW *win;
};
