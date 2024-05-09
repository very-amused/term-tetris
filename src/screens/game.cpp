#include <memory>

#include "game.hpp"
#include "../game/input.hpp"
#include "../ui.hpp"

using std::unique_ptr;

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
static const int GRID_HEIGHT = 20;
// Grid width in blocks
static const int GRID_WIDTH = 10;

void GameScreen::play(Screen &screen) {
	// Since the screen is occupying the whole window, we need to redraw the border
	draw_border();
	refresh();
	// Initialize state if needed
	if (!state) {
		state.reset(new GameState(GRID_HEIGHT, GRID_WIDTH));
	}

	// Initialize grid
	if (!grid) {
		static const int h = (GRID_HEIGHT * BLOCK_HEIGHT) + 2, // account for borders to keep centering accurate
								 		 w = (GRID_WIDTH * BLOCK_WIDTH) + 2;
		grid.reset(new GameGrid(win, GRID_HEIGHT, GRID_WIDTH, y_centered(h), x_centered(w)));
	}
	
	// Initialize gameplay input
	unique_ptr<GameInput> input(new GameInput(win));

	// Start game clock loop
	GameClock clock;
	while (!state->done) {
		// During each tick, the clock gets r/w access to state and ro access to grid
		clock.tick(state, input, grid);
		grid->draw(state);
	}

	// Restore input blocking
	input.reset();

	// After a game, we return to the main menu
	wclear(win);
	screen = Screen::Menu;
}
