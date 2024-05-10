#include "ui.hpp"
#include "DB.hpp"

#include <cursesw.h>
#include <memory>

using std::unique_ptr;

int main() {
	// Init DB
	unique_ptr<DB> db(new DB);
	if (db->init() != 0) {
		fprintf(stderr, "Error initializing DB: %s\n", db->errmsg);
		return 1;
	}

	// Init ncurses
	MainScreen screen;
	// Attach DB to ncurses ctx (db variable is invalid after this call)
	screen.attach_db(db);

	// Show the next screen based on screen ctx until the user has exited
	while (screen.screen != Screen::None) {
		screen.show_next();
	}

	return 0;
}
