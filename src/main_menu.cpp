#include "main_menu.hpp"
#include "ui.hpp"
#include "widgets/select.hpp"
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

void MenuScreen::show(Screen &screen) {
	// Draw window border
	draw_border_light(win);
	// Draw title
	draw_titlebar(win, "Term-Tetris");
	refresh();

	// Draw menu options
	const vector<SelectItem> select_opts = {
		SelectItem("Play"),
		SelectItem("High Scores"),
		SelectItem("Exit")
	};
	SelectMenu select_menu(win, &select_opts);
	int selection;
	select_menu.show(selection);

	// Wait for input
	wgetch(this->win);

	// Exit
	screen = Screen::None;
}

