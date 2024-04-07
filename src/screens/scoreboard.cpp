#include "scoreboard.hpp"

ScoreboardScreen::ScoreboardScreen() {
	// Create window	
	const int h = LINES;
	const int w = COLS;
	this->win = newwin(h, w, 0, 0);
}

ScoreboardScreen::~ScoreboardScreen() {
	delwin(this->win);
}

void ScoreboardScreen::show(Screen &screen) {
	// Get the top 10 scores
	// TODO: calculate n scores to get based on available lines
	screen = Screen::None;
}
