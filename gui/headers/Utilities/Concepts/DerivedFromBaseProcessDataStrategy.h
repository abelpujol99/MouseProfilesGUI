#pragma once
#include <type_traits>

#include "Strategies/TextStrategy/BaseProcessDataStrategy.h"

template <typename TProcessData, typename T>
concept DerivedFromBaseProcessDataStrategy = std::is_base_of_v<BaseProcessDataStrategy<T>, TProcessData>;