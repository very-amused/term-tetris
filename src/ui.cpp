#include "ui.hpp"
#include <cursesw.h>
#include <clocale>

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
