#pragma once
#include <chrono>
#include <ratio>

#include "state.hpp"
#include "../screens/game/grid.hpp"

// Framecounter with associated frame period
struct FrameCounter {
	size_t fc, fp;
};

struct GameClock {
	GameClock();

public:
	void tick(std::unique_ptr<GameState> &state, const std::unique_ptr<GameGrid> &grid);

private:
	// Set a fixed 60hz clock rate
	static const size_t TICK_FREQ = 60;
	// ref https://www.freecodecamp.org/news/cpp-std-chrono-api/
	// This article is terrible
	const std::chrono::duration<int, std::ratio<1, TICK_FREQ>> TICK_PERIOD{1};
	std::chrono::time_point<std::chrono::steady_clock> last_tick;

	FrameCounter are;
	FrameCounter gravity;
	// G = 1/2 for soft drop gravity
	static const size_t G_FP_SOFTDROP = 2;
};
