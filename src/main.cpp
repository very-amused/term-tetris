#include "ui.hpp"
#include <cursesw.h>

int main() {
	// Init ncurses
	MainScreen screen;

	while (screen.screen != Screen::None) {
		screen.show_next();
	}

	return 0;
}
