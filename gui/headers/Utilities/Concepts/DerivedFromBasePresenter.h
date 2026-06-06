#pragma once
#include <type_traits>

#include "MVP/Presenter/BasePresenter.h"

template <typename TPresenter>
concept DerivedFromBasePresenter = std::is_base_of_v<BasePresenter, TPresenter>;