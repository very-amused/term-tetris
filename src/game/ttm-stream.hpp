#pragma once
#include <memory>
#include <deque>
#include <random>

#include "blocks.hpp"

// A stream of random Tetrominos
struct TTMstream {
	TTMstream();

public:
	// Pop a block of the queue
	std::unique_ptr<Block> pop();
	// Peek at the second-last block in the queue,
	// used for the 'next' game window.
	const Block *peek_next() const;

	// Generate blocks as needed to ensure the queue has at least MIN_SIZE blocks.
	void populate();

private:
	// The absolute minimum size the queue is allowed to shrink to
	// before pushing more blocks
	static const size_t MIN_SIZE = 4;
	// How many blocks to generate and push onto the queue at a time
	static const size_t INCREMENT = 8;

	// RNG state
	std::unique_ptr<std::mt19937> rand_gen;
	std::uniform_int_distribution<size_t> rand_distrib;

	// Generate a random Tetromino and push it onto the queue
	void push_ttm();

	std::deque<std::unique_ptr<Block>> queue;
};
