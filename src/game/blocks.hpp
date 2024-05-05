#pragma once
#include "direction.hpp"

#include <cursesw.h>
#include <memory>

// A cell used to compose Tetris blocks.
struct BlockCell {
	BlockCell(WINDOW *block, int y, int x);
	~BlockCell() = default;
	BlockCell(const BlockCell &) = delete;

public:
	// Width of a block cell (columns)
	static const int WIDTH = 2;
	// Height of a block cell (lines)
	static const int HEIGHT = 1;

private:
	WINDOW *win;
};

// A Tetris block
struct Block {
	Block(bool cells[2][4]);
	~Block();
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
	std::unique_ptr<BlockCell> cells[4][4];
};

// The classic Tetris block set
static const Block blocks[] = {
	Block((bool[2][4]){
			{0, 1, 0, 0},
			{1, 1, 1, 0}}),
	Block((bool[2][4]){
			{1, 1, 1, 0},
			{0, 0, 1, 0}}),
	Block((bool[2][4]){
			{1, 1, 0, 0},
			{0, 1, 1, 0}}),
	Block((bool[2][4]){
			{1, 1, 0, 0},
			{1, 1, 0, 0}}),
	Block((bool[2][4]){
			{0, 1, 1, 0},
			{1, 1, 0, 0}}),
	Block((bool[2][4]){
			{1, 1, 1, 0},
			{1, 0, 0, 0}}),
	Block((bool[2][4]){
			{1, 1, 1, 1},
			{0, 0, 0, 0}})
};
