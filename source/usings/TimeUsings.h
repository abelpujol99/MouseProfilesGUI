#pragma once

#include <chrono>

#define DEFAULT_THREAD_SLEEP_MILLIS 20

using SystemClock = std::chrono::system_clock;
using Duration = std::chrono::duration<double, std::milli>;
using TimePoint = SystemClock::time_point;