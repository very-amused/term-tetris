#pragma once
#include <cursesw.h>
#include <memory>

#include "keybinds.hpp"
#include "screens.hpp"
#include "screens/main_menu.hpp"
#include "screens/game.hpp"
#include "DB.hpp"
#include "screens/scoreboard.hpp"

// Functional wrapper around ncursesw cchar_t
const cchar_t _cchar(wchar_t wcval);

// Border chars (heavy)
// ref https://en.cppreference.com/w/cpp/language/character_literal
static const cchar_t BORDER_HLINE = _cchar(L'━');
static const cchar_t BORDER_VLINE = _cchar(L'┃');
static const cchar_t BORDER_TL = _cchar(L'┏');
static const cchar_t BORDER_TR = _cchar(L'┓');
static const cchar_t BORDER_BL = _cchar(L'┗');
static const cchar_t BORDER_BR = _cchar(L'┛');
// Border chars (light)
static const cchar_t BORDER_HLINE_LIGHT = _cchar(L'─');
static const cchar_t BORDER_VLINE_LIGHT = _cchar(L'│');
static const cchar_t BORDER_TL_LIGHT = _cchar(L'┌');
static const cchar_t BORDER_TR_LIGHT = _cchar(L'┐');
static const cchar_t BORDER_BL_LIGHT = _cchar(L'└');
static const cchar_t BORDER_BR_LIGHT = _cchar(L'┘');
static const cchar_t BORDER_ML_LIGHT = _cchar(L'├');
static const cchar_t BORDER_MR_LIGHT = _cchar(L'┤');
// Border chars (pipe)
static const cchar_t BORDER_ML_PIPE = _cchar(L'╞');
static const cchar_t BORDER_MR_PIPE = _cchar(L'╡');
static const cchar_t BORDER_HLINE_PIPE = _cchar(L'═');

// Draw a heavy screen border
void draw_border(WINDOW *win);

// Draw a light border
void draw_border_light(WINDOW *win);

// TODO: document
int x_centered(int width);
int y_centered(int height);
int wx_centered(int wcols, int width);
int wy_centered(int wlines, int height);
void draw_hline(WINDOW *win,
		const cchar_t &BORDER_ML = BORDER_ML_LIGHT,
		const cchar_t &BORDER_HLINE = BORDER_HLINE_LIGHT,
		const cchar_t &BORDER_MR = BORDER_MR_LIGHT);
void draw_titlebar(WINDOW *win, std::string title);
// subwin/derwin refresh
void swrefresh(WINDOW *parent, WINDOW *sw);

// Main game menu + high scores
struct MenuScreen;

// Ncurses stdscr state
struct MainScreen {
	MainScreen();
	~MainScreen();
	// Ref jplank
	// We don't want to ever copy our global screen state
	MainScreen(const MainScreen &) = delete;

public:
	// Current screen
	Screen screen;
	// Show the currently set screen, creating it if needed
	void show_next();

	// Attach SQLite DB connection
	// (invalidates the ptr variable passed as parameter)
	void attach_db(std::unique_ptr<DB> &db);

private:
	// DB connection
	std::unique_ptr<DB> db;

	// Screens
	std::unique_ptr<MenuScreen> menu;
	std::unique_ptr<ScoreboardScreen> scoreboard;
	std::unique_ptr<GameScreen> game;
};

