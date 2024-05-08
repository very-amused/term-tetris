#pragma once
#include "state.hpp"

// Framecounter with associated frame period
struct FrameCounter {
	size_t fc, fp;
};

struct GameClock {
	GameClock();

public:
	void tick(std::unique_ptr<GameState> state);

private:
	// Fixed 60hz clock rate
	static const size_t FREQUENCY = 60;

	FrameCounter are;
	FrameCounter gravity;
	// G = 1/2 for soft drop gravity
	static const size_t G_FP_SOFTDROP = 2;
};
