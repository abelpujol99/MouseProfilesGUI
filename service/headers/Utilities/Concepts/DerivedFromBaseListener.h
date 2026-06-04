#pragma once
#include <type_traits>

#include "Listener/BaseListener.h"

template <typename TListener>
concept DerivedFromBaseListener = std::is_base_of_v<BaseListener, TListener>;