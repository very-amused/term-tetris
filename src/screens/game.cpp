#include "game.hpp"
#include "../ui.hpp"

GameScreen::GameScreen() {
	// Create window
	const int h = LINES;
	const int w = COLS;
	this->win = newwin(h, w, 0, 0);
}

GameScreen::~GameScreen() {
	delwin(this->win);
}

void GameScreen::show() {
	// Since the screen is occupying the whole window, we need to redraw the border
	draw_border();

	// Draw game grid
	if (!grid) {
		const int h_blocks = 20, w_blocks = 10;
		const int h = h_blocks * BlockCell::HEIGHT, w = w_blocks * BlockCell::WIDTH;
		grid.reset(new GameGrid(win, h_blocks, w_blocks, y_centered(h), x_centered(w)));
	}

	// After a game, we return to the main menu
	werase(win);
	wrefresh(win);
}
