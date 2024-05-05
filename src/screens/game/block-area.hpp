#pragma once
#include <cursesw.h>

// The block stacking area of the game, where the main gameplay takes place
struct BlockArea {
	BlockArea(WINDOW *parent);
	~BlockArea() = default;
	BlockArea(const BlockArea &) = delete;

public:

private:
	WINDOW *win;
};
