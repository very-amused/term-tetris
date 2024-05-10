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
	this->y = y;
	this->x = x;
	// Attach to ncurses pad
	pad = subpad(parent, BLOCK_HEIGHT, BLOCK_WIDTH, y * BLOCK_HEIGHT, x * BLOCK_WIDTH);
}

void Block::draw() {
	if (solid) {
		wbkgd(pad, color);
	}
}

void Block::redraw(int y_minrow, int x_mincol) {
	// TODO	
}
