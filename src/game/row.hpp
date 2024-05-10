#pragma once
#include <cursesw.h>
#include <vector>

#include "block.hpp"

struct GameGrid;

// A row pad capable of holding placed blocks
struct BlockRow {
	// Create an empty block row starting at (y, 0) block coords
	BlockRow(const GameGrid *grid, int y);
	~BlockRow();

public:
	void push_block(Block block, int x);
	void draw();

private:
	int y;
	const GameGrid *grid;
	// Main pad
	WINDOW *pad;
	// Block array
	std::vector<Block> blocks;
};
