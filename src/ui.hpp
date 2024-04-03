#pragma once
#include <cursesw.h>


// Functional wrapper around ncursesw cchar_t
const cchar_t _cchar(wchar_t wcval);

// Ncurses screen state
struct Screen {
	Screen();
	~Screen();
	// Ref jplank
	// We don't want to ever copy our global screen state
	Screen(const Screen &) = delete;

public:
	// Draw the main game menu
	void draw_menu();

private:
	// Border chars (heavy)
	// ref https://en.cppreference.com/w/cpp/language/character_literal
	const cchar_t BORDER_HLINE = _cchar(L'━');
	const cchar_t BORDER_VLINE = _cchar(L'┃');
	const cchar_t BORDER_TL = _cchar(L'┏');
	const cchar_t BORDER_TR = _cchar(L'┓');
	const cchar_t BORDER_BL = _cchar(L'┗');
	const cchar_t BORDER_BR = _cchar(L'┛');
	// Border chars (light)
	const cchar_t BORDER_HLINE_LIGHT = _cchar(L'─');
	const cchar_t BORDER_VLINE_LIGHT = _cchar(L'│');
	const cchar_t BORDER_TL_LIGHT = _cchar(L'┌');
	const cchar_t BORDER_TR_LIGHT = _cchar(L'┐');
	const cchar_t BORDER_BL_LIGHT = _cchar(L'└');
	const cchar_t BORDER_BR_LIGHT = _cchar(L'┘');

	// Draw heavy screen border
	void draw_border();
};
