#include "ui.hpp"
#include <cwchar>
#include <cursesw.h>

int main() {
	// Init ncurses
	Screen screen;

	screen.draw_menu();
	refresh();

	getch();


	return 0;
}
