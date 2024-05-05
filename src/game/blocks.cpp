#include "blocks.hpp"

BlockCell::BlockCell(WINDOW *block, int y, int x) {
	is_solid = true;
	// Create derived window if the block is solid
	win = derwin(block, WIDTH, HEIGHT, y * HEIGHT, x * WIDTH);
}

BlockCell::BlockCell() {
	is_solid = false;
	win = NULL;
}

