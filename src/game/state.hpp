#pragma once
#include <memory>

#include "collision.hpp"

struct GameState {
	GameState();
	std::unique_ptr<CollisionState> collision;
};
