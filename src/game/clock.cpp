#include "clock.hpp"
#include "ttm-stream.hpp"

using std::unique_ptr;

GameClock::GameClock() {
	are.fp = 18;
}

void GameClock::tick(unique_ptr<GameState> state) {
	/// ARE
	// Generate a new block and start ARE if needed
	if (!state->current_ttm) {
		state->current_ttm = state->ttm_stream->pop(); 
		are.fc = are.fp;
	}
	// Ignore input during ARE. No time to get competition-level fancy
	if (are.fc > 0) {
		are.fc--;
		return;
	}

	/// Drop
	// FIXME: next step is inputs + debouncing
}
