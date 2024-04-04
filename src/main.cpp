#include "ui.hpp"
#include "DB.hpp"
#include <cursesw.h>

int main() {
	// Init DB
	DB db;
	if (db.init() != 0) {
		fprintf(stderr, "Error initializing DB: %s\n", db.errmsg);
		return 1;
	}
	// Init ncurses
	MainScreen screen;

	while (screen.screen != Screen::None) {
		screen.show_next();
	}

	return 0;
}
