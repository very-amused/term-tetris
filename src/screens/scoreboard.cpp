#include "scoreboard.hpp"
#include "../ui.hpp"

ScoreboardScreen::ScoreboardScreen() {
	// Create window	
	const int h = LINES/1.5;
	const int w = COLS/2;
	win = newwin(h, w, y_centered(h), x_centered(w));
}

ScoreboardScreen::~ScoreboardScreen() {
	delwin(win);
}

void ScoreboardScreen::show(Screen &screen) {
	// Draw window border
	draw_border_light(win);
	// Draw title
	draw_titlebar(win, "Leaderboard");
	refresh();
	wgetch(win);

	// Get the top 10 scores
	// TODO: calculate n scores to get based on available lines
	screen = Screen::None;
}
