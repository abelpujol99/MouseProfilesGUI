#pragma once
#include <type_traits>

#include "Strategies/DrawStrategy/Rectangle/IDrawRectangleStrategy.h"

template <typename TDrawRectangleStrategy>
concept DerivedFromDrawRectangleStrategy = std::is_base_of_v<IDrawRectangleStrategy, TDrawRectangleStrategy>;