#include "select.hpp"
#include "../ui.hpp"
#include <cursesw.h>

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

	// Start at the top for selection
	// (or at the first selectable item)
	selection = 0;
	while (selection < items->size() && (*items)[selection].readonly) {
		selection++;
	}
	if ((*items)[selection].readonly) {
		selection = -1;
	}
}

void SelectMenu::draw() {
	static const auto highlight_attr = A_UNDERLINE | A_BOLD;

	// Reset cursor
	wmove(win, 0, 0);

	// Draw each option
	for (auto i = 0; i < items->size(); i++) {
		auto item = (*items)[i];
		// Draw separator
		draw_hline(win);

		// Draw text in new window (centered)
		WINDOW *item_win;
		if (i >= item_windows.size()) {
			item_win = derwin(win, 1, getmaxx(win) - 2, getcury(win), 1);
			item_windows.push_back(item_win);
		} else {
			item_win = item_windows[i];
		}
		if (i == selection) {
			wattron(item_win, highlight_attr);
		} else {
			wattroff(item_win, highlight_attr);
		}
		wmove(item_win, 0, getmaxx(item_win)/2 - item.text.size()/2);
		waddstr(item_win, (char *)item.text.c_str());

		// Move to next line
		wmove(win, getcury(win)+1, 0);
	}
}

bool SelectMenu::next_update() {
	switch (wgetch(win)) {
		case DOWN:
			if (selection < items->size()-1) {
				selection++;
				touchwin(win);
			}
			break;
		case UP:
			if (selection > 0) {
				selection--;
				touchwin(win);
			}
			break;
		case RETURN:
			return false;
	}

	return true;
}

const int SelectMenu::lines() {
	return getmaxy(win);
}
