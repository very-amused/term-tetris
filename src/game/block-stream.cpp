#include "block-stream.hpp"

using std::unique_ptr;

BlockStream::BlockStream() {
	// Seed RNG
	// ref https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
	std::random_device rd;
	rand_gen.reset(new std::mt19937(rd()));
	static const size_t block_templates_len = sizeof(BLOCK_TEMPLATES) / sizeof(BLOCK_TEMPLATES[0]);
	rand_distrib = std::uniform_int_distribution<size_t>(0, block_templates_len - 1);

	fill();
}

void BlockStream::fill() {
	if (queue.size() > MIN_SIZE) {
		return;
	}

	for (size_t i = 0; i < INCREMENT; i++) {
		push_block();
	}
}

inline void BlockStream::push_block() {
	// ref https://en.cppreference.com/w/cpp/container/deque/emplace_back
	queue.emplace_back(
			unique_ptr<Block>(
				new Block(BLOCK_TEMPLATES[rand_distrib(rand_gen)])
				)
		);
}

unique_ptr<Block> BlockStream::pop() {
	auto block = std::move(queue.front());
	queue.pop_front();

	return block;
}

const Block *BlockStream::peek_next() const {
	return queue[1].get();
}
