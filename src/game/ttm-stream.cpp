#include "ttm-stream.hpp"
#include <cstddef>
#include <cursesw.h>

using std::unique_ptr;

TTMstream::TTMstream() {
	// Seed RNG
	// ref https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
	std::random_device rd;
	rand_gen.reset(new std::mt19937(rd()));
	static const size_t block_templates_len = sizeof(TTM_TEMPLATES) / sizeof(TTM_TEMPLATES[0]);
	static const size_t block_colors_len = sizeof(BLOCK_COLORS) / sizeof(BLOCK_COLORS[0]);
	shape_distrib = std::uniform_int_distribution<size_t>(0, block_templates_len - 1);
	color_distrib = std::uniform_int_distribution<size_t>(1, block_colors_len);

	// Initialize colors
	for (size_t i = 0; i < block_colors_len; i++) {
		init_pair(i+1, COLOR_WHITE, BLOCK_COLORS[i]);
	}

	populate();
}

void TTMstream::populate() {
	if (queue.size() > MIN_SIZE) {
		return;
	}

	for (size_t i = 0; i < INCREMENT; i++) {
		push_ttm();
	}
}

void TTMstream::push_ttm() {
	// ref https://en.cppreference.com/w/cpp/container/deque/emplace_back
	queue.emplace_back(
			unique_ptr<TTM>(
				new TTM(TTM_TEMPLATES[shape_distrib(*rand_gen.get())], COLOR_PAIR(color_distrib(*rand_gen.get())))
				)
		);
}

unique_ptr<TTM> TTMstream::pop() {
	populate();
	auto block = std::move(queue.front());
	queue.pop_front();

	return block;
}

const TTM *TTMstream::peek_next() const {
	return queue[1].get();
}
