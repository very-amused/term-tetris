#pragma once
#include <cursesw.h>

#include "block.hpp"
#include "motion.hpp"
#include "collision.hpp"

struct GameGrid;

// Height of a Tetromino grid (blocks)
#define TTM_HEIGHT 4
// Width of a Tetromino grid (blocks)
#define TTM_WIDTH = 4

typedef bool TTMtemplate[2][4];

// A Tetromino composed of blocks
struct TTM {
	TTM(const TTMtemplate t);
	~TTM();
	TTM(const TTM &) = delete;

public:
	// Create a pad window and attach to stdscr
	void attach(const GameGrid *grid);
	// Render TTM (requires attach() first)
	void draw();

	// Move the TTM by 1 unit, returning false if collision prevented the movement
	bool move(Direction d, CollisionState &collision);
	// Rotate the TTM about its center, returning false if collision prevented the movement
	bool rotate(CollisionState &collision);

private:
	// TTM pad windows have the flexibility of arbitrary placement and cropping
	WINDOW *pad;
	const GameGrid *grid;

	// TTM grid x,y start coordinates.
	// (block units, relative to grid)
	int y, x;

	// TTM collision box x/y exclusive end coordinates.
	// (block units, relative to grid)
	const int collision_y() const;
	const int collision_x() const;

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
