#include <stdio.h>
#include <cursesw.h>
#include <memory>

#include "block.hpp"
#include "../ui.hpp"

using std::unique_ptr;

Block::Block(bool solid) {
	this->solid = solid;
	pad = NULL;
}

void Block::attach(WINDOW *parent, int y, int x) {
	// Attach to ncurses pad
	pad = subpad(parent, BLOCK_HEIGHT, BLOCK_WIDTH, y * BLOCK_HEIGHT, x * BLOCK_WIDTH);
}

void Block::draw() {
	static const cchar_t c = _cchar('0');
	if (solid) {
		wadd_wch(pad, &c);
	}
}
