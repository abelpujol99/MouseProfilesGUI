#pragma once

#include <type_traits>

#include "Frontend/UI/Strategies/RecycleViewStrategy/BaseRowCreationStrategy.h"

template <typename TRowCreation>
concept DerivedFromBaseRowCreationStrategy = std::is_base_of_v<BaseRowCreationStrategy, TRowCreation>;