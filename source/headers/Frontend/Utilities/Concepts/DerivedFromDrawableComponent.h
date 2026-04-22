#pragma once
#include <type_traits>

#include "Frontend/UI/Elements/Base/DrawableComponent.h"

template <typename TDrawableComponent>
concept DerivedFromDrawableComponent = std::is_base_of_v<DrawableComponent, TDrawableComponent>;