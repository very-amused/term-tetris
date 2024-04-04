#include "select.hpp"
#include "../ui.hpp"

using std::vector;
using std::string;

SelectItem::SelectItem(std::string text, bool readonly) {
	this->text = text;	
	this->readonly = readonly;
}

SelectMenu::SelectMenu(WINDOW *parent, const vector<SelectItem> *items) {
	// Calculate dimensions
	const int lines = (2 * items->size());
	const int cols = getmaxx(parent);
	const int y = getmaxy(parent) - lines - 1;
	const int x = 0;

	win = derwin(parent, lines, cols, y, x);
	this->items = items;
}

void SelectMenu::show(int &selection) {
	// Start at the top of the selection
	// (or the first selectable item)
	selection = 0;
	while (selection < items->size() && (*items)[selection].readonly) {
		selection++;
	}
	if ((*items)[selection].readonly) {
		selection = -1;
	}


	// Draw each option
	for (auto &item : *items) {
		// Draw separator
		draw_hline(win);
		// Draw text (centered)
		wmove(win, getcury(win), getmaxx(win)/2 - item.text.size()/2);
		waddstr(win, (char *)item.text.c_str());
		// Move to next line
		wmove(win, getcury(win)+1, 0);
	}
}
