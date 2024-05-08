#pragma once
#include <cursesw.h>

#include "motion.hpp"

// Height of a Tetromino block (rows)
static const int TTM_HEIGHT = 2;
// Width of a Tetromino block (columnms)
static const int TTM_WIDTH = 4;

// A Block used to compose TTMs
struct Block {
	// Construct a solid Block.
	// y and x are in *blocks* and will be scaled by block w/h
	Block(WINDOW *block, int y, int x);
	// Construct an empty Block. Empty blocks have no collision,
	// no visibility, and can overlap + clip
	Block();

	~Block() = default;
	// Make movable but not copyable
	Block(const Block &) = delete;
	Block(Block &&) = default;
	Block &operator=(Block &&) = default;

public:
	// Whether the block is visible and has collision
	bool is_solid;

private:
	WINDOW *win;
};

typedef bool TTMtemplate[2][4];

// A Tetromino composed of blocks
struct TTM {
	TTM(const TTMtemplate t);
	~TTM() = default;
	TTM(const TTM &) = delete;

public:
	// Move the block by 1 block height,
	// returning false if collision occured
	bool move(Direction d);
	// Rotate the block about its center,
	// returning false if collision occured
	bool rotate();

	// Attach block to a window for rendering
	// y/x are in blocks and will be scaled
	void attach(WINDOW *parent, int y, int x);
	
	// Render block (requires attach() first)
	void draw();

private:
	WINDOW *win;
	Block blocks[4][4];
};

// The classic Tetris Tetromino set
static const bool TTM_TEMPLATES[][2][4] = {
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
