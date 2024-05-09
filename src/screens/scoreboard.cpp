#include "scoreboard.hpp"
#include "../ui.hpp"
#include "../widgets/select.hpp"

#include <string>
#include <vector>
#include <memory>
#include <sqlite3.h>
#include <cursesw.h>

using std::vector;
using std::string;
using std::unique_ptr;

ScoreboardScreen::ScoreboardScreen() {
	// Create window	
	const int h = LINES/1.3;
	const int w = COLS/3;
	win = newwin(h, w, y_centered(h), x_centered(w));
}

ScoreboardScreen::~ScoreboardScreen() {
	delwin(win);
}

const vector<SelectItem> ScoreboardScreen::SELECT_OPTS = {
	SelectItem("Exit", 'q')
};

void ScoreboardScreen::show(Screen &screen, unique_ptr<DB> &db) {
	// Draw screen border
	draw_border(stdscr);
	// Draw window border
	draw_border_light(win);
	// Draw title
	draw_titlebar(win, "Leaderboard");
	refresh();

	if (select_menu == NULL) {
		select_menu.reset(new SelectMenu(win, SELECT_OPTS));
	}
	select_menu->draw();
	wrefresh(win);


	// Calculate how many scores we can display
	static const int titlebar_lines = 3;
	static const int y_start = titlebar_lines + 1; // Starting y
	const int n_scores = getmaxy(win) -  select_menu->lines() - y_start;

	// Prepare stmt to get the top n scores
	Stmt scores_stmt;
	int status = db->prepare_stmt("SELECT Score, PlayerName FROM Scores ORDER BY Score DESC LIMIT ?", scores_stmt);
	if (status != 0) {
		fprintf(stderr, "Failed to retrieve leaderboard: %s\n", sqlite3_errstr(status));
		screen = Screen::Menu;
		return;
	}
	// Set number of scores to retrieve via LIMIT ? parameter
	// ref https://sqlite.org/c3ref/bind_blob.html
	status = sqlite3_bind_int(scores_stmt.stmt, 1, n_scores);
	if (status != 0) {
		fprintf(stderr, "Failed to bind leaderboard stmt parameter (LIMIT = %d): %s\n", n_scores, sqlite3_errstr(status));
		screen = Screen::Menu;
		return;
	}

	// Retrieve and display each score
	int y = y_start;
	while (status = sqlite3_step(scores_stmt.stmt), status == SQLITE_ROW) {
		wmove(win, y, 1);
		// Get score and player name from sqlite3 row
		auto score = sqlite3_column_int64(scores_stmt.stmt, 0);
		const char *player_name = (const char *)sqlite3_column_text(scores_stmt.stmt, 1);

		// TODO: this format sucks, we should make a grid for this
		// Use format: {name} - {score}
		// for displaying player scores
		string score_line = string(player_name) + " - " + std::to_string(score);
		waddstr(win, (char *)score_line.c_str());

		y++;
	}
	if (y == y_start) {
		static const string msg = "No scores yet.";
		// We use (msg.size() - 1) to account for the fact that our brains don't seem to consider punctuation when seeing text as centered
		wmove(win, y_start + y_centered(n_scores - y), getmaxx(win)/2 - (msg.size() - 1)/2);
		waddstr(win, (char *)msg.c_str());
	}

	// Display the text we just wrote
	wrefresh(win);

	while (select_menu->next_update()) {
		select_menu->draw();
	}

	wclear(win);
	screen = Screen::Menu;
}
