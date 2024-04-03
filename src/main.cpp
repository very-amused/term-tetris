#include "ui.hpp"
#include <cursesw.h>

// ref https://dev.to/tbhaxor/introduction-to-ncurses-part-1-1bk5

int main() {
	// Init ncurses
	Screen screen;

	printw("Yes\n");
	refresh();

	getch();

	return 0;
}
