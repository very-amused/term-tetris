#pragma once
#include <cursesw.h>

// Height of a Tetromino block (rows)
static const int BLOCK_HEIGHT = 2;
// Width of a Tetromino block (columnms)
static const int BLOCK_WIDTH = 4;


// A Block used to compose TTMs
struct Block {
	// y and x are in *blocks* and will be scaled
	Block(bool solid = false);

	~Block() = default;
	// Make movable but not copyable
	Block(const Block &) = delete;
	Block(Block &&) = default;
	Block &operator=(Block &&) = default;

public:
	// Whether the block is visible and has collision
	bool solid;

	// Attach to parent pad at (y, x) relative
	void attach(WINDOW *parent, int y, int x);

	void draw();

private:
	// Block windows must be pads due to their parent TTM windows being pads
	WINDOW *pad;
};
