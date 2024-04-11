#pragma once
#include <cursesw.h>
#include <vector>
#include <string>

struct SelectItem {
	SelectItem(std::string text, bool readonly = false);

public:
	std::string text;	
	bool readonly;
};

// A selection widget for displaying multiple selectable or highlightable strings
struct SelectMenu {
	SelectMenu(WINDOW *parent, const std::vector<SelectItem> *items);
	~SelectMenu() = default;

public:
	// Initially draw everything
	void draw();

	// Block until a selection change.
	// A return value of false indicates that the selection was confirmed and the caller should proceed
	bool next_update();

	// Get the number of lines occupied by a SelectMenu
	const int lines();

	// The index of the currently selected item
	int selection;

private:
	const std::vector<SelectItem> *items;
	WINDOW *win;
	// Item windows holding only text - used for highlighting via wattr
	std::vector<WINDOW *> item_windows;
};

