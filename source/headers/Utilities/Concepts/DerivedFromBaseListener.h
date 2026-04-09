#pragma once
#include "Backend/Listener/BaseListener.h"

template <typename TListener>
concept DerivedFromBaseListener = std::is_base_of_v<BaseListener, TListener>;