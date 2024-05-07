#pragma once
#include <memory>

#include "collision.hpp"
#include "blocks.hpp"

struct GameState {
	GameState();

	std::unique_ptr<CollisionState> collision;
	std::unique_ptr<Block> current_piece;
	// TODO: input state
};
