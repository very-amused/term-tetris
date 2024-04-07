#pragma once
#include <cursesw.h>
#include <memory>
#include "screens.hpp"
#include "screens/main_menu.hpp"
#include "screens/game.hpp"

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

// Movement keys
#define LEFT 'h'
#define UP 'k'
#define DOWN 'j'
#define RIGHT 'l'
#define RETURN '\n'

// Draw a light border, for use with derived (sub) windows
void draw_border_light(WINDOW *win);

// TODO: document
int x_centered(int width);
int y_centered(int height);
void draw_hline(WINDOW *win,
		const cchar_t &BORDER_ML = BORDER_ML_LIGHT,
		const cchar_t &BORDER_HLINE = BORDER_HLINE_LIGHT,
		const cchar_t &BORDER_MR = BORDER_MR_LIGHT);
void draw_titlebar(WINDOW *win, std::string title);

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

private:
	// Draw a heavy screen border
	void draw_border();

	// Screens
	std::unique_ptr<MenuScreen> menu;
	std::unique_ptr<GameScreen> game;
};

