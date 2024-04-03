#include "ui.hpp"
extern "C" {
#include <cursesw.h>
}
#include <clocale>

Screen::Screen() {
	// Initialize locale
	setlocale(LC_ALL, "");

	// Initialize screen
	// ref: man ncurses
	// ref man cbreak
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
