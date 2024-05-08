#pragma once
#include <cursesw.h>

#include "block.hpp"
#include "motion.hpp"
#include "collision.hpp"

struct GameGrid;

// Height of a Tetromino grid (blocks)
#define TTM_HEIGHT 4
// Width of a Tetromino grid (blocks)
#define TTM_WIDTH 4


struct TTMtemplate {
	bool blocks[2][4];
	// (y,x) origin coords for clockwise rotation.
	// negative coords denote that rotation is not permitted
	short origin[2];
};

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

	// Collision box x/y start coordinates - inclusive
	// (block units, relative to grid)
	const int y_start() const;
	const int x_start() const;

	// Collision box x/y end coordinates - exclusive
	// (block units, relative to grid)
	const int collision_y() const;
	const int collision_x() const;

	Block blocks[4][4];
	// (y, x) origin  coords for clockwise rotation.
	// negative coords denote that rotation is not permitted
	short origin[2];
};

// The classic Tetris Tetromino set
static const TTMtemplate TTM_TEMPLATES[] = {
	{
		{{1, 1, 1, 0},
		 {0, 1, 0, 0}}, {0, 1}},
	{
		{{1, 1, 1, 0},
		 {0, 0, 1, 0}}, {0, 1}},
	{
		{{1, 1, 0, 0},
		 {0, 1, 1, 0}}, {0, 1}},
	{
		{{1, 1, 0, 0},
		 {1, 1, 0, 0}}, {-1, -1}},
	{
		{{0, 1, 1, 0},
		 {1, 1, 0, 0}}, {0, 1}},
	{
		{{1, 1, 1, 0},
		 {1, 0, 0, 0}}, {0, 1}},
	{
		{{1, 1, 1, 1},
		 {0, 0, 0, 0}}, {0, 2}}
};
