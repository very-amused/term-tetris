#include <ncurses.h>
#include <stdio.h>
#include <cursesw.h>

#include "block.hpp"
#include "../ui.hpp"

Block::Block(bool solid) {
	this->solid = solid;
	pad = NULL;
}

void Block::attach(WINDOW *parent, int y, int x) {
	// Attach to ncurses pad
	pad = subpad(parent, BLOCK_HEIGHT, BLOCK_WIDTH, y * BLOCK_HEIGHT, x * BLOCK_WIDTH);
}

void Block::draw() {
	if (solid) {
		wbkgd(pad, color);
	}
}
