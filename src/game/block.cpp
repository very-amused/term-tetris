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

void Block::reattach(WINDOW *parent, int y, int x) {
	// Detach
	if (!solid) {
		return;
	}
	delwin(pad);

	// Reattach
	attach(parent, y, x);
}

void Block::draw() {
	if (solid) {
		wbkgd(pad, color);
	}
}

void Block::refresh(int y_minrow, int x_mincol, size_t row, size_t col) {
	if (!solid) {
		return;
	}

	y_minrow += row * BLOCK_HEIGHT;
	x_mincol += col * BLOCK_WIDTH;
	int y_maxrow = y_minrow + BLOCK_HEIGHT;
	int x_maxcol = x_mincol + BLOCK_WIDTH;
	prefresh(pad, 0, 0,
			y_minrow, x_mincol, y_maxrow, x_maxcol);
}
