#pragma once
#include <cursesw.h>

#include "motion.hpp"

// A cell used to compose Tetris blocks.
struct BlockCell {
	// Construct a solid BlockCell.
	// y and x are in *cells* and will be scaled by cell w/h
	BlockCell(WINDOW *block, int y, int x);
	// Construct an empty BlockCell. Empty cells have no collision,
	// no visibility, and can overlap + clip
	BlockCell();

	~BlockCell() = default;
	// Make movable but not copyable
	BlockCell(const BlockCell &) = delete;
	BlockCell(BlockCell &&) = default;
	BlockCell &operator=(BlockCell &&) = default;

public:
	// Width of a block cell (columns)
	static const int WIDTH = 2;
	// Height of a block cell (lines)
	static const int HEIGHT = 1;

	// Whether the cell is visible and has collision
	bool is_solid;
	

private:
	WINDOW *win;
};

typedef bool BlockTemplate[2][4];

// A Tetris block
struct Block {
	Block(const BlockTemplate t);
	~Block() = default;
	Block(const Block &) = delete;

public:
	// Move the block by 1 cell height,
	// returning false if collision occured
	bool move(Direction d);
	// Rotate the block about its center,
	// returning false if collision occured
	bool rotate();


private:
	WINDOW *win;
	BlockCell cells[4][4];
};

// The classic Tetris block set
static const bool BLOCK_TEMPLATES[][2][4] = {
	{
		{0, 1, 0, 0},
		{1, 1, 1, 0}},
	{
		{1, 1, 1, 0},
		{0, 0, 1, 0}},
	{
		{1, 1, 0, 0},
		{0, 1, 1, 0}},
	{
		{1, 1, 0, 0},
		{1, 1, 0, 0}},
	{
		{0, 1, 1, 0},
		{1, 1, 0, 0}},
	{
		{1, 1, 1, 0},
		{1, 0, 0, 0}},
	{
		{1, 1, 1, 1},
		{0, 0, 0, 0}}
};
