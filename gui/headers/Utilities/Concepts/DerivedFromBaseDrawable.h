#pragma once
#include <type_traits>

#include "UI/Elements/Base/BaseDrawable.h"

template <typename TDrawable>
concept DerivedFromBaseDrawable = std::is_base_of_v<BaseDrawable, TDrawable>;