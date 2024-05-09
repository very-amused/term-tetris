#include "state.hpp"

GameState::GameState(int h_blocks, int w_blocks) {
	// Init RNG and TTM (piece) stream
	ttm_stream.reset(new TTMstream);
	// Init collision
	collision.reset(new CollisionState(h_blocks, w_blocks));

	level = 1;
	done = false;
}
