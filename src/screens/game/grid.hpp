#pragma once
#include <cursesw.h>
#include <memory>

#include "../../game/state.hpp"

// The block grid where gameplay takes place
struct GameGrid {
	// h/w are in Block units and are scaled
	// y/x are in lines/cols and are *not* scaled
	GameGrid(WINDOW *parent, int h_blocks, int w_blocks, int y, int x);
	~GameGrid() = default;
	GameGrid(const GameGrid &) = delete;

public:
	void draw(const std::unique_ptr<GameState> &state);

	// Get the grid's height in blocks
	const int height_blocks() const;
	// Get the grid's width in blocks
	const int width_blocks() const;

	// Get the grid's height in lines
	const int height_lines() const;
	// Get the grid's width in cols
	const int width_cols() const;

	// Get the grid's absolute y offset in lines
	const int offset_y() const;
	// Get the grid's absolute x offset in cols
	const int offset_x() const;

private:
	WINDOW *parent;
	/* A critical runtime invariant is that the dimensions of the grid window
	are always even multiples of BLOCK_HEIGHT and BLOCK_WIDTH respectively.
	This invariant is ensured by the constructor requiring block units,
	which are then scaled to lines/cols.
	
	This invariant makes the grid's window the single source of truth for its dimensions,
	both in block units and in line/col units. This window is additionally the single source
	of truth for the grid's offsets with respect to its parent window and the screen. */
	WINDOW *win;
};
