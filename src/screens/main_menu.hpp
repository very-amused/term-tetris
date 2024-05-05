#pragma once
#include "../screens.hpp"
#include "../widgets/select.hpp"

#include <cursesw.h>
#include <memory>
#include <string>

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

	static const std::vector<SelectItem> SELECT_OPTS;
	std::unique_ptr<SelectMenu> select_menu;

	void draw_title(std::string title);
};
