#pragma once
#include <type_traits>

#include "Strategies/TextStrategy/BaseProcessDataStrategy.h"

template <typename TProcessData>
concept DerivedFromBaseProcessDataStrategy = std::is_base_of_v<BaseProcessDataStrategy, TProcessData>;