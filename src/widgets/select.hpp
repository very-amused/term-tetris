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
	void show(int &selection);

private:
	const std::vector<SelectItem> *items;
	WINDOW *win;
};

