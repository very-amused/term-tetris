#include "game_screen.hpp"

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
	// TODO
	screen = Screen::None;
}
