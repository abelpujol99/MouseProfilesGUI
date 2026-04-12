#pragma once

#include "Frontend/UI/Elements/Complex/Screen.h"

class ScreenFactory
{
public:

    [[nodiscard]] static std::unique_ptr<Screen> CreateProfileScreen(ImVec2&& position, bool isHidden);
};
