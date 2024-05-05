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

void GameScreen::show(Screen &screen) {
	// Since the screen is occupying the whole window, we need to redraw the border
	draw_border();
	getch();

	// After a game, we return to the main menu
	werase(win);
	wrefresh(win);
	screen = Screen::Menu;
}
