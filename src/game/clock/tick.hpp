#pragma once
#include <cstddef>
// ref https://www.freecodecamp.org/news/cpp-std-chrono-api/
// This article is terrible ^
// ref https://en.cppreference.com/w/cpp/chrono/duration
#include <chrono>
#include <ratio>


// Set a fixed 60hz clock rate
static const size_t TICK_FREQ = 60;

// Duration type which can be used to measure ticks
typedef std::chrono::duration<int, std::ratio<1, TICK_FREQ>> GameClock_tick_t;

// The duration of 1 tick of the GameClock
static const GameClock_tick_t TICK_PERIOD{1};
