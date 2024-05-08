#pragma once
#include <cursesw.h>

#include "block.hpp"
#include "motion.hpp"

// Height of a Tetromino grid (blocks)
#define TTM_HEIGHT 4
// Width of a Tetromino grid (blocks)
#define TTM_WIDTH = 4

typedef bool TTMtemplate[2][4];

// A Tetromino composed of blocks
struct TTM {
	TTM(const TTMtemplate t);
	~TTM() = default;
	TTM(const TTM &) = delete;

public:
	// Create a pad window and attach to stdscr
	void attach(const WINDOW *grid);
	// Render block (requires attach() first)
	void draw();

	// Move the block by 1 unit.
	void move(Direction d);
	// Rotate the block about its center.
	bool rotate();

private:
	// TTM pad windows have the flexibility of arbitrary placement and cropping
	WINDOW *pad;
	const WINDOW *grid;

	// We need to know our Grid's dimensions
	
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
