#pragma once
#include <memory>

#include "collision.hpp"
#include "ttm.hpp"
#include "ttm-stream.hpp"

struct GameState {
	// Initialize game state (including RNG) for play
	GameState(int h_blocks, int w_blocks);

	// The current game level (1-10)
	unsigned short level;
	// Whether the game is finished
	bool done;

	// Current Tetromino
	std::unique_ptr<TTM> current_ttm;
	// Stream/queue used for TTM (piece) gen
	std::unique_ptr<TTMstream> ttm_stream;
	// Collision bitmap
	std::unique_ptr<CollisionState> collision;
	// TODO: input state
};
