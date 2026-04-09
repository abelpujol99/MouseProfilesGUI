#pragma once
#include "Frontend/UI/Strategies/TextStrategy/BaseProcessDataStrategy.h"

template <typename TProcessData, typename T>
concept DerivedFromBaseProcessDataStrategy = std::is_base_of_v<BaseProcessDataStrategy<T>, TProcessData>;