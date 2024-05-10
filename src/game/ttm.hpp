#pragma once
#include <cursesw.h>
#include <memory>

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

struct BlockPoints {
	std::vector<Point> coords;
	std::vector<Block *> blocks;
};

// A Tetromino composed of blocks
struct TTM {
	TTM(const TTMtemplate t, chtype color);
	~TTM();
	TTM(const TTM &) = delete;

public:
	// Create a pad window and attach to stdscr and collision state
	void attach(const GameGrid *grid, std::unique_ptr<CollisionState> &collision);
	// Return whether the TTM has been attached for rendering
	bool attached();
	// Render TTM (requires attach() first)
	void draw();

	// Move the TTM by 1 unit, returning false if collision prevented the movement
	bool move(Direction d, std::unique_ptr<CollisionState> &collision);
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

	// Piece color for solid blocks
	chtype color;	

	// Get solid block coordinates for transformation
	BlockPoints block_points();

	Block blocks[4][4];
	// (y, x) origin  coord for clockwise rotation.
	// negative coords denote that rotation is not permitted
	short origin[2];
};
