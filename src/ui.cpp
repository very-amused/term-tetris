#include "ui.hpp"
#include <clocale>
#include <cstdlib>
#include <cursesw.h>
#include <string>
#include <memory>

using std::string;
using std::unique_ptr;

const cchar_t _cchar(wchar_t wcval) {
	wchar_t tmp[] = {wcval, '\0'};
	cchar_t wc;
	setcchar(&wc, tmp, WA_NORMAL, COLOR_PAIR(0), NULL);
	return wc;
}

MainScreen::MainScreen() {
	// ref https://dev.to/tbhaxor/introduction-to-ncurses-part-1-1bk5
	// Initialize locale
	setlocale(LC_ALL, "");

	// ref man ncurses
	// ref man cbreak
	// Initialize screen
	initscr();
	// Disable terminal buffering
	cbreak();
	// Don't echo typed characters
	noecho();
	// Hide terminal cursor
	curs_set(0);

	// Don't flush tty output upon SIGINT
	intrflush(stdscr, FALSE);
	// Enable keypad support
	keypad(stdscr, TRUE);

	// Draw the outer screen border
	draw_border();
	// Set the main menu as the first window to be shown
	screen = Screen::Menu;
}

MainScreen::~MainScreen() {
	// Close DB
	db.reset();

	// Free owned screens
	menu.reset();
	scoreboard.reset();
	game.reset();

	// Reset terminal state before exiting
	endwin();
}

void MainScreen::show_next() {
	switch (screen) {
	case Screen::None:
		return;

	case Screen::Menu:
		// Create menu window if it doesn't exist
		if (!menu) {
			menu.reset(new MenuScreen);
		}
		// Show main menu, deferring input handling until the user takes an action prompting a new screen
		menu->show(screen);
		break;

	case Screen::Leaderboard:
		if (!scoreboard) {
			scoreboard.reset(new ScoreboardScreen);
		}
		scoreboard->show(screen, db);
		break;

	case Screen::Game:
		// Create game screen window if it doesn't exist
		if (!game) {
			game.reset(new GameScreen);
		}
		game->show(screen);
	}
}

void MainScreen::attach_db(unique_ptr<DB> &db) {
	this->db.swap(db);
}

void draw_border() {
	border_set(&BORDER_VLINE, &BORDER_VLINE,
			&BORDER_HLINE, &BORDER_HLINE,
			&BORDER_TL, &BORDER_TR,
			&BORDER_BL, &BORDER_BR);
}

void draw_border_light(WINDOW *win) {
	wborder_set(win, &BORDER_VLINE_LIGHT, &BORDER_VLINE_LIGHT,
			&BORDER_HLINE_LIGHT, &BORDER_HLINE_LIGHT,
			&BORDER_TL_LIGHT, &BORDER_TR_LIGHT,
			&BORDER_BL_LIGHT, &BORDER_BR_LIGHT);
}

int x_centered(int width) {
	return COLS/2 - width/2;
}

int y_centered(int height) {
	return LINES/2 - height/2;
}

void draw_hline(WINDOW *win,
		const cchar_t &BORDER_ML,
		const cchar_t &BORDER_HLINE,
		const cchar_t &BORDER_MR) {
	wadd_wch(win, &BORDER_ML);
	whline_set(win, &BORDER_HLINE, getmaxx(win) - 2);
	wmove(win, getcury(win), getmaxx(win) - 1);
	wadd_wch(win, &BORDER_MR);
}

void draw_titlebar(WINDOW *win, string title) {
	// Draw top pipe bar
	wmove(win, 1, 0);
	draw_hline(win, BORDER_ML_PIPE, BORDER_HLINE_PIPE, BORDER_MR_PIPE);

	// Draw title (centered)
	wmove(win, 2, getmaxx(win)/2 - title.size()/2);
	waddstr(win, (char *)title.c_str());

	// Draw bottom pipe bar
	wmove(win, 3, 0);
	draw_hline(win, BORDER_ML_PIPE, BORDER_HLINE_PIPE, BORDER_MR_PIPE);
}
