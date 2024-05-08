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

// Grid height in blocks
static const int H_BLOCKS = 20;
// Grid width in blocks
static const int W_BLOCKS = 10;

void GameScreen::play(Screen &screen) {
	// Since the screen is occupying the whole window, we need to redraw the border
	draw_border();
	refresh();
	// Initialize state if needed
	if (!state) {
		state.reset(new GameState(H_BLOCKS, W_BLOCKS));
	}

	// Draw game grid
	if (!grid) {
		static const int h = H_BLOCKS * TTM_HEIGHT,
								 		 w = W_BLOCKS * TTM_WIDTH;
		grid.reset(new GameGrid(win, H_BLOCKS, W_BLOCKS, y_centered(h), x_centered(w)));
	}
	grid->draw(state);

	// After a game, we return to the main menu
	wclear(win);
	screen = Screen::Menu;
}
