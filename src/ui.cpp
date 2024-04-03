#include "ui.hpp"
#include <clocale>
#include <cursesw.h>

const cchar_t _cchar(wchar_t wcval) {
	wchar_t tmp[] = {wcval, '\0'};
	cchar_t wc;
	setcchar(&wc, tmp, WA_NORMAL, COLOR_PAIR(0), NULL);
	return wc;
}

Screen::Screen() {
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

	// Don't flush tty output upon SIGINT
	intrflush(stdscr, FALSE);
	// Enable keypad support
	keypad(stdscr, TRUE);
}

Screen::~Screen() {
	// Reset terminal state before exiting
	endwin();
}

void Screen::draw_menu() {
	draw_border();
}

void Screen::draw_border() {
	border_set(&BORDER_VLINE, &BORDER_VLINE,
			&BORDER_HLINE, &BORDER_HLINE,
			&BORDER_TL, &BORDER_TR,
			&BORDER_BL, &BORDER_BR);
}
