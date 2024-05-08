#include "block.hpp"

Block::Block(bool solid) {
	this->solid = solid;
	pad = NULL;
}

void Block::attach(WINDOW *parent, int y, int x) {
	pad = subpad(parent, BLOCK_HEIGHT, BLOCK_WIDTH, y * BLOCK_HEIGHT, x * BLOCK_WIDTH);
}
