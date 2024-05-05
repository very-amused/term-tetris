#include "block-stream.hpp"
#include <cstdlib>

BlockStream::BlockStream() {
	fill();
}

void BlockStream::fill() {
	if (queue.size() > MIN_SIZE) {
		return;
	}

	rand();
}
