#pragma once
#include <chrono>
#include <ratio>

#include "input.hpp"
#include "state.hpp"
#include "../screens/game/grid.hpp"

#include "clock/tick.hpp"

// Framecounter with associated frame period
struct FrameCounter {
	size_t fc, fp; // TODO: Frame counters will currently overflow and break things if we skip any frames
};

struct GameClock {
	GameClock();


public:
	void tick(std::unique_ptr<GameState> &state, std::unique_ptr<GameInput> &input, const std::unique_ptr<GameGrid> &grid);

private:
	std::chrono::time_point<std::chrono::steady_clock> last_tick;

	FrameCounter are;
	FrameCounter gravity;
	// G = 1/2 for soft drop gravity
	static const size_t G_FP_SOFTDROP = 2;
};
