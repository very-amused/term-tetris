#include "clock.hpp"
#include "motion.hpp"
#include "ttm-stream.hpp"
#include <chrono>
#include <cstdlib>
#include <cursesw.h>
#include <thread>

using std::unique_ptr;
using std::chrono::steady_clock;

GameClock::GameClock() {
	are.fp = 18;
#ifdef DEBUG
	gravity.fp = 10; // Start drops much faster for quicker debugging
#else
	gravity.fp = 30;
#endif
	gravity.fc = 0;

	// Initialze tick period
	last_tick = last_tick.min(); // Set last_tick to zero value
}


void GameClock::tick(std::unique_ptr<GameState> &state, std::unique_ptr<GameInput> &input, const std::unique_ptr<GameGrid> &grid) {
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
		state->current_ttm->attach(grid.get(), state->collision);
		are.fc = are.fp;
	}
	// Ignore input during ARE. No time to get competition-level fancy
	if (are.fc > 0) {
		are.fc -= ticks_elapsed;
		return;
	}

	// FIXME: rotate

	// Translate
	input->getkeys();
	const Direction move_lateral = input->get_direction(true);
	if (move_lateral == Direction::Left || move_lateral == Direction::Right) {
		state->current_ttm->move(move_lateral, state->collision);
	}


	/// Drop
	// Apply soft drop input if present
	// TODO: softdrop is experiencing a hold delay and should not be
	size_t gravity_fp;
	if (input->get_direction(false) == Direction::Down) {
		gravity_fp = G_FP_SOFTDROP;
		gravity.fc %= gravity_fp;
	} else {
		gravity_fp = gravity.fp;
	}
	if (gravity.fc > 0) {
		gravity.fc -= ticks_elapsed;
		return;
	}

	// Handle placement
	if (!state->current_ttm->move(Direction::Down, state->collision)) {
		state->current_ttm->decompose(state->rows);
		(void)state->current_ttm.release(); // FIXME?

		// Handle clears
		auto clears = state->collision->check_clears();	
		for (auto y : clears) {
			state->rows[y].reset();
			if (y > 0) {
				for (size_t ys = y; ys > 0; ys--) {
					state->rows[ys-1].swap(state->rows[ys]);
					if (state->rows[ys]) {
						state->rows[ys]->y = ys;
					}
				}
			}
		}

		return;
	}
	gravity.fc = gravity_fp;
}
