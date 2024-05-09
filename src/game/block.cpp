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

void Block::attach(WINDOW *parent, unique_ptr<CollisionState> &collision, Point p) {
	// Attach to ncurses pad
	pad = subpad(parent, BLOCK_HEIGHT, BLOCK_WIDTH, p.y * BLOCK_HEIGHT, p.x * BLOCK_WIDTH);
	// Attach to collision state
	collision->fill_block(p.y, p.x);
}

void Block::draw() {
	static const cchar_t c = _cchar('0');
	if (solid) {
		wadd_wch(pad, &c);
	}
}
