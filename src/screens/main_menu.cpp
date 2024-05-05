#include "main_menu.hpp"
#include "../ui.hpp"
#include "../widgets/select.hpp"
#include <string>

using std::string;
using std::vector;

MenuScreen::MenuScreen() {
	// Create window
	const int h = LINES/1.75;
	const int w = COLS/3;
	this->win = newwin(h, w, y_centered(h), x_centered(w));
}

MenuScreen::~MenuScreen() {
	delwin(this->win);
}

static const vector<SelectItem> SELECT_OPTS = {
	SelectItem("Play"),
	SelectItem("High Scores"),
	SelectItem("Exit", 'q')
};

void MenuScreen::show(Screen &screen) {
	// Draw window border
	draw_border_light(win);
	// Draw title
	draw_titlebar(win, "Term-Tetris");
	refresh();

	// Draw menu options
	SelectMenu select_menu(win, SELECT_OPTS);
	select_menu.draw();
	wrefresh(win); // Widget cuts into parent window, so we need a refresh

	while (select_menu.next_update()) {
		select_menu.draw();
	}

	// Handle final selection
	switch (select_menu.selection) {
	case 0:
		// Play
		screen = Screen::Game;
		break;
	case 1:
		// High Scores
		screen = Screen::Leaderboard;
		break;
	case 2:
		// Exit
		screen = Screen::None;
	}
}

