#include "clock.hpp"
#include "ttm-stream.hpp"
#include <chrono>
#include <thread>

using std::unique_ptr;
using std::chrono::duration;
using std::chrono::time_point;
using std::chrono::steady_clock;
using std::this_thread::sleep_until;

GameClock::GameClock() {
	are.fp = 300;
	// Initialze tick period
	last_tick = last_tick.min(); // Set last_tick to zero value
}

void GameClock::tick(unique_ptr<GameState> &state, const unique_ptr<GameGrid> &grid) {
	// Sleep until ready for the next tick to start
	unsigned int ticks_elapsed = 1;
	if (last_tick != last_tick.min()) {
		std::this_thread::sleep_until(last_tick + TICK_PERIOD);
		// Try to keep physics from lagging behind. We'll see how this goes
		ticks_elapsed = (steady_clock::now() - last_tick) / TICK_PERIOD;
	}
	last_tick = steady_clock::now();

	/// ARE
	// Generate a new block and start ARE if needed
	if (!state->current_ttm) {
		state->current_ttm = state->ttm_stream->pop();
		state->current_ttm->attach(grid.get());
		are.fc = are.fp;
	}
	// Ignore input during ARE. No time to get competition-level fancy
	if (are.fc > 0) {
		are.fc -= ticks_elapsed;
		return;
	}

	/// Drop
	// FIXME: next step is inputs + debouncing
}
