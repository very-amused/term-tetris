#pragma once

// Ncurses screen state
struct Screen {
	Screen();
	~Screen();
	// Ref jplank
	// We don't want to ever copy our global screen state
	Screen(const Screen &) = delete;

public:
	void draw_border();

private:
	// Border chars (heavy)
	// ref https://en.cppreference.com/w/cpp/language/character_literal
	static const wchar_t BORDER_HLINE = L'━';
	static const wchar_t BORDER_VLINE = L'┃';
	static const wchar_t BORDER_TL = L'┏';
	static const wchar_t BORDER_TR = L'┓';
	static const wchar_t BORDER_BL = L'┗';
	static const wchar_t BORDER_BR = L'┛';
	// Border chars (light)
	static const wchar_t BORDER_HLINE_LIGHT = L'─';
	static const wchar_t BORDER_VLINE_LIGHT = L'│';
	static const wchar_t BORDER_TL_LIGHT = L'┌';
	static const wchar_t BORDER_TR_LIGHT = L'┐';
	static const wchar_t BORDER_BL_LIGHT = L'└';
	static const wchar_t BORDER_BR_LIGHT = L'┘';

};
