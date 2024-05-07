#include "loop.hpp"

using std::unique_ptr;

GameClock::GameClock() {
	are.fp = 18;
}

void GameClock::tick(unique_ptr<GameState> state) {
	// Generate a new block and start ARE if needed
}
