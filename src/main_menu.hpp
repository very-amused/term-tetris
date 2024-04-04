#pragma once
#include <cursesw.h>
#include <string>
#include "screen.hpp"

struct MenuScreen {
	MenuScreen();
	~MenuScreen();
	MenuScreen(const MenuScreen &) = delete;

public:
	// Show the menu and wait until the user makes a selection,
	// setting win_state to reflect the user's choice 
	void show(Screen &screen);

private:
	WINDOW *win;
	void draw_title(std::string title);
};
