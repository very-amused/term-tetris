#pragma once
#include <cursesw.h>
#include <vector>
#include <string>

struct SelectItem {
	SelectItem(std::string text, char shortcut = -1, bool readonly = false);

public:
	std::string text;	
	bool readonly;
	// Optional keyboard shortcut (only considered when > 0) which acts equivalent to selecting and confirming
	// the item when pressed
	char shortcut;
};

// Shortcut tuple of (char, index) used to optimize shortcut handling
struct SelectShortcut_ {
	char key;
	size_t index;
};

// A selection widget for displaying multiple selectable or highlightable strings
struct SelectMenu {
	SelectMenu(WINDOW *parent, const std::vector<SelectItem> items);
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
	WINDOW *win;

	std::vector<SelectItem> items;
	std::vector<SelectShortcut_> shortcuts;
	// Item windows holding only text - used for highlighting via wattr
	std::vector<WINDOW *> item_windows;
};

