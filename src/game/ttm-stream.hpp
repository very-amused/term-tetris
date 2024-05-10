#pragma once
#include <memory>
#include <deque>
#include <random>

#include "ttm.hpp"

// A stream of random Tetrominos
struct TTMstream {
	TTMstream();

public:
	// Pop a block of the queue
	std::unique_ptr<TTM> pop();
	// Peek at the second-last block in the queue,
	// used for the 'next' game window.
	const TTM *peek_next() const;

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
	std::uniform_int_distribution<size_t> shape_distrib;
	std::uniform_int_distribution<size_t> color_distrib;

	// Generate a random Tetromino and push it onto the queue
	void push_ttm();

	std::deque<std::unique_ptr<TTM>> queue;
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

// Some colors
// TODO: better color distribution, level-based color schemes
const short BLOCK_COLORS[] = {
		COLOR_RED,
		COLOR_BLUE,
		COLOR_GREEN,
		COLOR_MAGENTA,
		COLOR_CYAN,
		COLOR_YELLOW
};

