#pragma once
#include <type_traits>

#include "../../Device/VirtualDevice/BaseVirtualDevice.h"

template<typename TVirtualDevice>
concept DerivedFromIVirtualDevice = std::is_base_of_v<BaseVirtualDevice, TVirtualDevice>;
