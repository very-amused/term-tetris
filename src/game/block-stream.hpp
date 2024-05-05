#pragma once
#include "blocks.hpp"

#include <queue>

// A stream of random Tetris blocks
struct BlockStream {
	BlockStream();

public:
	// Pop a block of the queue
	const Block pop();
	// Peek at the second-last block in the queue,
	// used for the 'next' game window
	const Block &peek();

private:
	// The absolute minimum size the queue is allowed to shrink to
	// before pushing more blocks
	static const size_t MIN_SIZE = 4;
	// How many blocks to generate and push onto the queue at a time
	static const size_t INCREMENT = 8;
	// Generate blocks as needed to ensure the queue has at least MIN_SIZE blocks.
	void fill();

	std::queue<Block> queue;
};
