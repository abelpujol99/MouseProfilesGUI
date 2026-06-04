#pragma once

#include <chrono>

using SystemClock = std::chrono::system_clock;
using Duration = std::chrono::duration<double, std::milli>;
using TimePoint = SystemClock::time_point;