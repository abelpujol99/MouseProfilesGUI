#pragma once

#include "imgui.h"

class IPosition
{
public:

    virtual ~IPosition() = default;

    [[nodiscard]] virtual ImVec2 GetParentPosition() const = 0;

    [[nodiscard]] virtual ImVec2 GetParentBottomRightPosition() const = 0;

};