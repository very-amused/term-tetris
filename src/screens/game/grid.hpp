#pragma once
#include <cursesw.h>
#include <memory>

#include "../../game/state.hpp"

// The block grid where gameplay takes place
struct GameGrid {
	// h/w are in BlockCell units and are scaled
	// y/x are in lines/cols and are *not* scaled
	GameGrid(WINDOW *parent, int h_cells, int w_cells, int y, int x);
	~GameGrid() = default;
	GameGrid(const GameGrid &) = delete;

public:
	void draw(const std::unique_ptr<GameState> &state);

private:
	WINDOW *parent;
	WINDOW *win;
};
