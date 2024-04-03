#pragma once
#include <cursesw.h>


// Wrapper around ncursesw cchar_t providing RAII from wchar_t
struct CChar {
	CChar(wchar_t wcval);

	// Wide character
	cchar_t wc;
};

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
	const CChar BORDER_HLINE = CChar(L'━');
	const CChar BORDER_VLINE = CChar(L'┃');
	const CChar BORDER_TL = CChar(L'┏');
	const CChar BORDER_TR = CChar(L'┓');
	const CChar BORDER_BL = CChar(L'┗');
	const CChar BORDER_BR = CChar(L'┛');
	// Border chars (light)
	const CChar BORDER_HLINE_LIGHT = CChar(L'─');
	const CChar BORDER_VLINE_LIGHT = CChar(L'│');
	const CChar BORDER_TL_LIGHT = CChar(L'┌');
	const CChar BORDER_TR_LIGHT = CChar(L'┐');
	const CChar BORDER_BL_LIGHT = CChar(L'└');
	const CChar BORDER_BR_LIGHT = CChar(L'┘');

	// Draw heavy screen border
	void draw_border();
};
