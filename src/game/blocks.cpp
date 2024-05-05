#include "blocks.hpp"


BlockCell::BlockCell(WINDOW *block, int y, int x) {
	// Create derived window
	win = derwin(block, WIDTH, HEIGHT, y, x);
}


