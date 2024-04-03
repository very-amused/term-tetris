#include "ui.hpp"
#include <clocale>
#include <cursesw.h>

CChar::CChar(wchar_t wcval) {
	wchar_t tmp[] = {wcval, 0};
	setcchar(&wc, tmp, WA_NORMAL, COLOR_PAIR(0), NULL);
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
	border_set(&BORDER_VLINE.wc, &BORDER_VLINE.wc,
			&BORDER_HLINE.wc, &BORDER_HLINE.wc,
			&BORDER_TL.wc, &BORDER_TR.wc,
			&BORDER_BL.wc, &BORDER_BR.wc);
}
