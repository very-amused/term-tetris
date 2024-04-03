#include "main_menu.hpp"
#include "ui.hpp"
#include <string>

using std::string;

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
	draw_border_light(this->win);
	// Draw title
	draw_title();

	refresh();

	// Wait for input
	wgetch(this->win);

	// Exit
	screen = Screen::None;
}

void MenuScreen::draw_title() {
	// Draw top pipe bar
	wmove(win, 1, 0);
	draw_pipe_hline(win);

	// Draw title (centered)
	static char title[] = "Term-Tetris";
	wmove(win, 2, getmaxx(win)/2 - (sizeof(title) - 1)/2);
	waddstr(win, title);

	// Draw bottom pipe bar
	wmove(win, 3, 0);
	draw_pipe_hline(win);
}
